# Process Internals & Communication Deep Dive

## Memory Layout (Systems Programmer View)

### Single Process with Multiple Threads
```
Virtual Address Space (64-bit: 0x0000000000000000 - 0x7FFFFFFFFFFF)

┌─────────────────────────────────────┐ 0x7FFF...
│    Kernel Space (not accessible)     │
├─────────────────────────────────────┤ 0x7FFF... (user limit)
│                                     │
│    Stack - Thread 3  [SP₃]         │ ← Each thread has own stack
│    (grows downward ↓)              │    8MB default on Linux
│                                     │
├─────────────────────────────────────┤
│    Stack - Thread 2  [SP₂]         │
├─────────────────────────────────────┤
│    Stack - Thread 1  [SP₁]         │
├─────────────────────────────────────┤
│    Stack - Main Thread [SP₀]       │
├─────────────────────────────────────┤
│                                     │
│         [Memory Mapping Area]       │  mmap() allocations, shared libs
│                                     │
├─────────────────────────────────────┤
│                                     │
│    Heap (grows upward ↑)           │ ← SHARED by all threads
│    [malloc/new allocates here]     │   This is where pthread communicates!
│                                     │
├─────────────────────────────────────┤
│    BSS (uninitialized globals)     │ ← SHARED
├─────────────────────────────────────┤
│    Data (initialized globals)      │ ← SHARED
├─────────────────────────────────────┤
│    Text (code/instructions)        │ ← SHARED (read-only)
└─────────────────────────────────────┘ 0x0000...

Key Points:
- Each thread gets own stack (8MB), grows downward from high address
- Stack Pointer (SP) register is per-thread
- Heap, Data, BSS, Text segments are SHARED among all threads
- Thread Local Storage (TLS) exists but not shown here
```

## Communication Mechanisms

### 1. INTRA-PROCESS (Between Threads in Same Process)

```
Thread 1                                Thread 2
┌──────────┐                           ┌──────────┐
│  Stack   │                           │  Stack   │
│  ┌────┐  │                           │  ┌────┐  │
│  │var1│  │                           │  │var2│  │
│  └────┘  │                           │  └────┘  │
└────┬─────┘                           └────┬─────┘
     │                                      │
     │     Both access same memory         │
     └──────────┬──────────────────────────┘
                │
         ┌──────▼──────┐
         │ Shared Heap │
         │  ┌────────┐ │
         │  │ Data   │ │◄─── Direct memory access
         │  └────────┘ │     Cost: 1-200 CPU cycles
         └─────────────┘

CPU Instructions (x86-64):
  mov rax, [shared_ptr]     ; Load from shared memory
  inc QWORD [shared_ptr]    ; Atomic increment
  lock inc QWORD [counter]  ; Atomic with lock prefix
```

### 2. INTER-PROCESS (Between Different Processes)

#### A. Pipe IPC
```
Process A (Writer)              Kernel              Process B (Reader)
┌──────────┐                ┌──────────┐           ┌──────────┐
│User Space│                │  Kernel  │           │User Space│
│  ┌────┐  │  write(fd)     │  Buffer  │  read(fd) │  ┌────┐  │
│  │data│──┼────────────────►│  4KB-    │◄──────────┼──│buf │  │
│  └────┘  │  syscall       │  64KB    │  syscall  │  └────┘  │
└──────────┘                └──────────┘           └──────────┘

Steps:
1. Process A calls write() → context switch to kernel
2. Kernel copies data from Process A to pipe buffer
3. Kernel wakes Process B if waiting
4. Process B calls read() → context switch to kernel
5. Kernel copies data from pipe buffer to Process B
Cost: ~1000-5000 CPU cycles (2 system calls + 2 copies)
```

#### B. Shared Memory IPC
```
Process A                      Physical RAM         Process B
┌──────────┐                  ┌──────────┐         ┌──────────┐
│Virtual   │  mmap()          │ Physical │  mmap() │Virtual   │
│Address   │                  │  Memory  │         │Address   │
│          │                  │          │         │          │
│0x7F00... ├──────────────────►│0x89AB... │◄────────┤0x6E00... │
│          │  Maps to same    │  [DATA]  │  Maps   │          │
│          │  physical page   │          │  here   │          │
└──────────┘                  └──────────┘         └──────────┘

Steps:
1. One process creates shared memory segment (shm_open/mmap)
2. Both processes map same physical pages to their virtual space
3. Direct memory access - NO kernel involvement after setup!
4. Still need synchronization (semaphores/mutex in shared memory)
Cost: ~100 cycles (page table walk) + regular memory access
```

## CPU Perspective: What Happens on Memory Access?

### Thread Accessing Shared Variable
```
1. CPU executes: mov rax, [shared_var]
2. Check TLB (Translation Lookaside Buffer): Hit? → Fast path
3. If TLB miss: Walk page tables (4 levels on x86-64)
4. Check CPU caches:
   L1 cache (4 cycles, ~32KB per core)
   L2 cache (12 cycles, ~256KB per core)
   L3 cache (40 cycles, ~8MB shared)
   RAM (100-200 cycles)
5. If another core modified it: Cache coherency protocol (MESI/MOESI)

Total: 1-200 cycles depending on cache state
```

### Process Using Pipe IPC
```
1. CPU executes: syscall (write)
2. Mode switch: User → Kernel (save registers, ~50 cycles)
3. Validate file descriptor, check permissions
4. Copy data from user space to kernel pipe buffer (100-1000 cycles)
5. Update pipe metadata, wake reader process
6. Mode switch: Kernel → User (restore registers, ~50 cycles)

Reader process:
7. CPU executes: syscall (read)
8. Mode switch: User → Kernel
9. Copy data from kernel pipe buffer to user space
10. Mode switch: Kernel → User

Total: 1000-5000 cycles + context switch overhead
```

## Register State (Per-Thread)

Each thread maintains its own register state:
```
General Purpose:  RAX, RBX, RCX, RDX, RSI, RDI, R8-R15
Stack Pointers:   RSP (stack pointer), RBP (base pointer)
Instruction:      RIP (instruction pointer)
Flags:           RFLAGS (zero, carry, overflow, etc.)

Shared by all threads in process:
- Page Table Base Register (CR3) - same virtual→physical mapping
- File Descriptor Table
- Signal Handlers
- Process ID (PID)
```

## Context Switch Details

### Thread Context Switch (within same process)
```
1. Save current thread registers to Thread Control Block (TCB)
2. Load next thread registers from its TCB
3. Update stack pointer (RSP) to new thread's stack
4. Jump to new instruction pointer (RIP)

NO NEED TO:
- Change page tables (CR3 unchanged)
- Flush TLB
- Switch address space

Cost: ~1-2 microseconds
```

### Process Context Switch (between different processes)
```
1. Save current process registers to Process Control Block (PCB)
2. Load next process registers from its PCB
3. Switch page tables (load CR3 with new page table base)
4. Flush TLB (all cached virtual→physical translations invalid!)
5. Update memory management unit (MMU)
6. Switch process ID (PID)
7. Jump to new instruction pointer

Cost: ~10-20 microseconds (TLB flush is expensive!)
```

## Real-World Implications

### When Threads Win (Intra-Process)
- **Web Server**: Thread pool handling requests (shared cache, connections)
- **Database**: Query threads share buffer pool
- **Game Engine**: Physics, rendering, AI threads share game state
- **Performance**: Sub-microsecond communication

### When Processes Win (Inter-Process)  
- **Web Browser**: Separate process per tab (isolation, security)
- **Chrome**: GPU process, network process, renderer processes
- **Nginx**: Master-worker architecture (privilege separation)
- **Security**: Memory isolation, fault tolerance

### Hybrid Approach
- **Apache**: Multi-process + multi-threaded (MPM worker)
- **PostgreSQL**: Process per connection + background workers
- **Node.js**: Single-threaded event loop + worker processes

## Summary Table

| Aspect | Intra-Process (Threads) | Inter-Process |
|--------|------------------------|---------------|
| **Memory** | Shared heap/globals | Isolated |
| **Stack** | Separate per thread | Separate per process |
| **IPC Cost** | 1-200 cycles | 1000-5000 cycles |
| **Setup** | Simple | Complex (fork/exec) |
| **Safety** | Need locks | Isolated by default |
| **Use Case** | Performance | Security/Isolation |
| **Context Switch** | 1-2 μs | 10-20 μs |
| **TLB Flush** | No | Yes |
