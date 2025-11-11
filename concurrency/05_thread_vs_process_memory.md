# Thread vs Process Memory Layout - Complete Comparison

## The Fundamental Difference

**Process Memory**: Each process gets its OWN complete address space
**Thread Memory**: All threads SHARE one address space, each gets own stack

---

## Visual Comparison: 2 Processes vs 1 Process with 2 Threads

```
TWO SEPARATE PROCESSES                    ONE PROCESS, TWO THREADS
(Completely Isolated)                     (Shared Address Space)

Process A         Process B               Single Process
┌─────────────┐  ┌─────────────┐         ┌─────────────────┐
│ Kernel      │  │ Kernel      │         │ Kernel Space    │
├─────────────┤  ├─────────────┤         ├─────────────────┤
│ Stack A     │  │ Stack B     │         │ Stack Thread 1  │ ← 0x16fc7b000
│ 0x7FF...    │  │ 0x7FF...    │         ├─────────────────┤
│             │  │             │         │ Stack Thread 2  │ ← 0x16fd07000
│             │  │             │         ├─────────────────┤
│             │  │             │         │ (room for more) │
├─────────────┤  ├─────────────┤         ├─────────────────┤
│ Heap A      │  │ Heap B      │         │                 │
│ Different!  │  │ Different!  │         │ SHARED HEAP     │ ← 0x100869be0
│             │  │             │         │ (all threads)   │
├─────────────┤  ├─────────────┤         ├─────────────────┤
│ Data A      │  │ Data B      │         │ SHARED DATA     │ ← 0x10021c000
│ int g=100   │  │ int g=200   │         │ int global=100  │ (global_var)
├─────────────┤  ├─────────────┤         ├─────────────────┤
│ Code A      │  │ Code B      │         │ SHARED CODE     │ ← 0x10020c620
│ main() {...}│  │ main() {...}│         │ functions       │ (print_memory_layout)
└─────────────┘  └─────────────┘         └─────────────────┘

Can't access      Can't access           Thread 1 and Thread 2
each other's      each other's           access SAME memory!
memory!           memory!                
```

---

## Real Memory Addresses from Our Program

```
Thread 1 Memory Map:                    Thread 2 Memory Map:
┌────────────────────────────────┐     ┌────────────────────────────────┐
│ LOCAL VARIABLES (Stack)        │     │ LOCAL VARIABLES (Stack)        │
│   local_var   : 0x16fc7af28 ←─┼─────┼─→ Different address!           │
│                                │     │   local_var   : 0x16fd06f28    │
├────────────────────────────────┤     ├────────────────────────────────┤
│ HEAP ALLOCATIONS               │     │ HEAP ALLOCATIONS               │
│   heap_var    : 0x100869be0 ←─┼─────┼─→ Same region!                 │
│                                │     │   heap_var    : 0x100869bf0    │
├────────────────────────────────┤     ├────────────────────────────────┤
│ GLOBAL VARIABLES (Data)        │     │ GLOBAL VARIABLES (Data)        │
│   global_var  : 0x10021c000 ←─┼─────┼─→ EXACT same address!          │
│                                │     │   global_var  : 0x10021c000    │
├────────────────────────────────┤     ├────────────────────────────────┤
│ THREAD LOCAL STORAGE           │     │ THREAD LOCAL STORAGE           │
│   tls_var     : 0x100869c50 ←─┼─────┼─→ Different!                   │
│   value: 100                   │     │   tls_var     : 0x100869d10    │
│                                │     │   value: 200                   │
├────────────────────────────────┤     ├────────────────────────────────┤
│ CODE (Text Segment)            │     │ CODE (Text Segment)            │
│   function    : 0x10020c620 ←─┼─────┼─→ EXACT same address!          │
└────────────────────────────────┘     └────────────────────────────────┘

KEY OBSERVATION:
- Stack: Different for each thread (0x16fc... vs 0x16fd...)
- Heap:  Same region, different allocations (0x100869...)
- Global: EXACT SAME address (0x10021c000)
- TLS:   Different addresses (0x100869c50 vs 0x100869d10)
- Code:  EXACT SAME address (0x10020c620)
```

---

## Address Space Layout (64-bit Linux/macOS typical)

```
High Address (0x7FFFFFFFFFFF)
│
│  ┌─────────────────────────────────────┐
│  │    Kernel Space (not accessible)    │
│  │    ~128 TB                          │
└──┴─────────────────────────────────────┴── 0x7FFF... (user limit)
   │                                     │
   │ Stack Growth Direction ↓            │
   ├─────────────────────────────────────┤
   │  Thread 1 Stack (8 MB)              │  0x16fc7b000 - 0x16fcfb000
   │  ┌────────────────────────┐         │
   │  │ local vars, params     │         │
   │  │ return addresses       │         │
   │  │ saved registers        │         │
   │  └────────────────────────┘         │
   ├─────────────────────────────────────┤
   │  Guard Page (4 KB)                  │  ← Causes SIGSEGV on overflow
   ├─────────────────────────────────────┤
   │  Thread 2 Stack (8 MB)              │  0x16fd07000 - 0x16fe07000
   │  ┌────────────────────────┐         │
   │  │ local vars, params     │         │
   │  │ return addresses       │         │
   │  └────────────────────────┘         │
   ├─────────────────────────────────────┤
   │  Guard Page (4 KB)                  │
   ├─────────────────────────────────────┤
   │  ... more thread stacks ...         │
   ├─────────────────────────────────────┤
   │                                     │
   │  Memory Mapped Region               │
   │  - Shared libraries (.so/.dylib)    │
   │  - mmap() allocations               │  0x100000000 - 0x7FFF...
   │  - Thread Local Storage (TLS)       │
   │                                     │
   ├─────────────────────────────────────┤
   │                                     │
   │  Heap (grows upward ↑)             │
   │  ┌────────────────────────┐         │
   │  │ new/malloc allocations │         │  0x100869be0 (example)
   │  │ SHARED by all threads  │         │
   │  └────────────────────────┘         │
   │                                     │
   ├─────────────────────────────────────┤
   │  BSS (Uninitialized Data)           │  0x10021d000 (example)
   │  - Globals without initializer      │
   ├─────────────────────────────────────┤
   │  Data (Initialized Data)            │  0x10021c000 (example)
   │  - Global variables (int global=100)│
   │  - Static variables                 │
   ├─────────────────────────────────────┤
   │  Text (Code/Instructions)           │  0x10020c000 (example)
   │  - Compiled functions               │
   │  - Read-only, executable            │
   └─────────────────────────────────────┘
Low Address (0x0000000000000000)
```

---

## What the CPU Sees (Register Perspective)

### Thread 1 Running:
```
CPU Registers (Thread 1 Context):
┌────────────────────────────────┐
│ RIP (Instruction Ptr)          │ → Points to code at 0x10020c620
│ RSP (Stack Pointer)            │ → Points to 0x16fc7af28 (Thread 1 stack)
│ RBP (Base Pointer)             │ → Points to Thread 1 stack frame
│ RAX, RBX, RCX, RDX, etc.       │ → Thread 1's working data
└────────────────────────────────┘
```

### Context Switch to Thread 2:
```
1. OS saves Thread 1 registers to Thread Control Block (TCB)
2. OS loads Thread 2 registers from its TCB

CPU Registers (Thread 2 Context):
┌────────────────────────────────┐
│ RIP (Instruction Ptr)          │ → Points to code at 0x10020c620 (same code!)
│ RSP (Stack Pointer)            │ → Points to 0x16fd06f28 (Thread 2 stack)
│ RBP (Base Pointer)             │ → Points to Thread 2 stack frame
│ RAX, RBX, RCX, RDX, etc.       │ → Thread 2's working data
└────────────────────────────────┘
```

**Critical**: Only RSP changes! Code (RIP) can be same location!

---

## Thread Control Block (TCB) - What OS Maintains

```c
// Kernel data structure (simplified)
struct thread_control_block {
    // Saved CPU state (during context switch)
    uint64_t rax, rbx, rcx, rdx, rsi, rdi;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rsp;           // Stack pointer
    uint64_t rbp;           // Base pointer
    uint64_t rip;           // Instruction pointer
    uint64_t rflags;        // CPU flags
    
    // Thread metadata
    int tid;                // Thread ID (visible in htop/ps)
    int state;              // RUNNING, READY, BLOCKED
    int priority;           
    
    // Stack info
    void* stack_base;       // 0x16fc7b000 for Thread 1
    size_t stack_size;      // 8388608 bytes (8 MB)
    
    // TLS
    void* tls_base;         // Thread Local Storage base
    
    // Scheduling
    uint64_t cpu_time_used;
    int cpu_affinity;       // Which CPU cores can run this
    
    // Synchronization
    void* waiting_on;       // Mutex/condvar it's blocked on
};
```

---

## Stack Growth Detail

```
Thread 1 Stack (grows downward):

Top of stack (high address): 0x16fcfb000
│
├─ Current SP: 0x16fc7af28 (during our program)
│  ┌────────────────┐
│  │ local_var = 1  │  ← Active stack frame
│  │ return addr    │
│  ├────────────────┤
│  │ previous frame │
│  │ ...            │
│  └────────────────┘
│
│  [Unused stack space ~8 MB]
│
└─ Bottom of stack (low address): 0x16fc7b000 (stack base)
   [Guard Page]  ← Accessing this causes SIGSEGV (stack overflow)
```

---

## Why This Design?

### Advantages of Shared Address Space (Threads):
1. **Fast communication**: Just write to shared memory
   ```cpp
   shared_var = 42;  // Other threads see it immediately
   ```

2. **Efficient memory**: One copy of code/data for all threads
   ```
   Process with 10 threads: ~8 MB × 10 = 80 MB for stacks
                           + 1 copy of code/heap (not 10!)
   ```

3. **Fast context switch**: Only save/restore registers + RSP
   - No TLB flush
   - No page table change
   - ~1-2 microseconds

### Disadvantages:
1. **Need synchronization**: Race conditions possible
2. **One thread crashes**: Can corrupt shared heap → all threads affected
3. **Debugging harder**: Concurrent bugs are non-deterministic

---

## Key Differences: Process vs Thread Memory

| Aspect | Process | Thread |
|--------|---------|--------|
| **Address Space** | Own complete space | Share parent's space |
| **Code Segment** | Separate copy | Shared |
| **Data/BSS** | Separate | Shared |
| **Heap** | Separate | Shared |
| **Stack** | One per process | One per thread |
| **TLS** | Not applicable | Per-thread |
| **Global Variables** | Separate copies | Same copy |
| **CR3 Register** | Different (page table) | Same |
| **Context Switch** | Change CR3, flush TLB | Just change RSP/registers |
| **Memory Overhead** | High (~4 MB minimum) | Low (~8 MB for stack) |

---

## Summary: The Mental Model

**Think of threads like this:**

```
Imagine a library (process) with one book collection (code/data/heap).

Multiple readers (threads) are studying at different tables (stacks).
- They can all read the same books (shared memory)
- They can write notes on the books (modify shared data)
- Each has their own notepad (stack/local variables)
- Each has their own bookmark (TLS - thread local storage)

When a reader switches (context switch):
- Just swap which table you're sitting at (change RSP)
- The books stay where they are (no memory remapping)

When you switch between libraries (process switch):
- Move to different building (change CR3, flush TLB)
- Completely different book collection
- Much slower!
```

---

## From Our Program Output

Notice these patterns:

1. **Stack addresses are far apart**:
   - Thread 1: `0x16fc7af28`
   - Thread 2: `0x16fd06f28`
   - Difference: ~4 MB (room for stack + guard pages)

2. **Heap addresses are close**:
   - Thread 1 heap: `0x100869be0`
   - Thread 2 heap: `0x100869bf0`
   - Difference: 16 bytes (two allocations in same heap)

3. **Global address is IDENTICAL**:
   - Both threads: `0x10021c000`
   - Same variable, same location!

4. **Code address is IDENTICAL**:
   - Both threads: `0x10020c620`
   - Same function, same location!

This proves threads share everything except stacks!
