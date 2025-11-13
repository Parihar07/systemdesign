# Process, Threads & Concurrency

## Systems Programmer Perspective

Understanding concurrency is critical for:
- Writing high-performance applications
- Understanding OS internals
- Debugging race conditions and deadlocks
- Efficient resource utilization

## Basics (Definition + Syntax)

### What is a Process?
- Independent execution unit with its own virtual address space (code, data, heap, stack).
- Isolated from other processes; switching processes changes the address space.

Minimal syntax (create, exec, wait):
```cpp
#include <unistd.h>     // fork, execlp
#include <sys/wait.h>   // waitpid

int main() {
	pid_t pid = fork();
	if (pid == 0) {                 // child
		execlp("ls", "ls", "-1", (char*)nullptr); // replace child image
		_exit(127);                  // only if exec fails
	}
	int status = 0;
	waitpid(pid, &status, 0);        // parent waits
}
```

### What is a Thread?
- Lightweight execution unit within a process; shares code/data/heap with other threads.
- Each thread has its own stack and register state.

Minimal syntax (create, join, detach):
```cpp
#include <thread>

void work(int x) { /* do something */ }

int main() {
	std::thread t(work, 42); // start thread with function + arg
	t.join();                 // wait for it to finish

	std::thread d([]{ /* background */ });
	d.detach();               // run independently (no join)
}
```

## Learning Path

### Part 0: Single vs Multi-thread Basics ✅
📄 [00_single_thread_basics.cpp](00_single_thread_basics.cpp)
📄 [00_multi_thread_basics.cpp](00_multi_thread_basics.cpp)

Focus: simple syntax, one concept per file.
Compare a single-thread compute vs the same split across threads.
Measure time; keep code readable and minimal.

### Part 0.1: Quick Syntax – Thread & Process Creation ✅
📄 [06_thread_create_basics.cpp](06_thread_create_basics.cpp)  
📄 [07_process_create_basics.cpp](07_process_create_basics.cpp)

Focus: minimal, readable syntax only.
- Thread: start with function, lambda, passing args, join vs detach
- Process: `fork()` child, `execlp("ls")`, `waitpid()` in parent

### Part 1: Process vs Thread Fundamentals ✅
📄 [01_process_vs_thread.cpp](01_process_vs_thread.cpp)

**Topics Covered:**
- Memory layout (stack, heap, code, data segments)
- Context switching costs and performance comparison
- fork() vs std::thread
- Global variable sharing vs isolation
- When to use processes vs threads

**Key Insights:**
- Threads share code/data/heap, separate stacks
- Thread context switch ~10x faster than process
- Process isolation provides security, threads provide performance

---

### Part 2: IPC & Process Internals ✅
📄 [02_ipc_internals.cpp](02_ipc_internals.cpp)  
📖 [03_process_internals_deep_dive.md](03_process_internals_deep_dive.md)

**Topics Covered:**
- Intra-process communication (threads - shared memory)
- Inter-process communication (pipes, shared memory)
- Performance comparison: atomic operations vs syscalls
- TCB and PCB in kernel memory
- Context switch mechanics (thread vs process)

**Key Insights:**
- Intra-process: 1-200 CPU cycles (direct memory access)
- Inter-process: 1000-5000 cycles (syscall overhead)
- TCB/PCB never swapped (always in kernel RAM)
- Shared memory IPC fastest for processes

---

### Part 3: Thread Memory Layout ✅
📄 [04_thread_memory_layout.cpp](04_thread_memory_layout.cpp)  
📖 [05_thread_vs_process_memory.md](05_thread_vs_process_memory.md)

**Topics Covered:**
- Virtual address space layout
- Stack independence (each thread has own 8MB stack)
- Heap sharing among threads
- Thread Local Storage (thread_local keyword)
- Actual memory addresses demonstration

**Key Insights:**
- Threads don't have separate memory layouts like processes
- All threads share ONE address space with separate stacks
- Virtual addresses are just labels, physical RAM stores data
- TLS provides per-thread variables without locking

---

### Part 4: Synchronization Primitives (Coming Soon)
- std::mutex and lock_guard
- std::condition_variable
- std::atomic types
- Memory ordering

### Part 5: Common Concurrency Problems (Coming Soon)
- Race conditions
- Deadlocks
- Starvation
- Priority inversion

### Part 6: Concurrency Patterns (Coming Soon)
- Thread pool
- Producer-Consumer
- Reader-Writer
- Future/Promise

### Part 7: Real-world Examples (Coming Soon)
- Multi-threaded server
- Concurrent queue
- Parallel task executor

## Compilation
```bash
# Compile with thread support
make FILE=filename.cpp run

# Or directly:
g++ -std=c++17 -pthread filename.cpp -o program && ./program
```

## Key Takeaways (Updated)

### Process vs Thread
- ✅ Threads share memory → faster but need synchronization
- ✅ Processes isolated → safer but higher overhead
- ✅ Thread context switch: ~1-2 μs vs Process: ~10-20 μs
- ✅ TLB flush only needed for process switch

### Memory & Communication
- ✅ Threads share: heap, globals, code, file descriptors
- ✅ Threads separate: stack (8MB each), CPU registers, TLS
- ✅ Intra-process IPC: Direct memory access (1-200 cycles)
- ✅ Inter-process IPC: Syscalls + copying (1000-5000 cycles)

### Virtual Memory
- ✅ Virtual addresses are labels/indexes, not storage
- ✅ MMU translates virtual → physical addresses
- ✅ Page tables map virtual to physical pages
- ✅ Swap is overflow storage, not virtual memory itself

### Kernel Structures
- ✅ TCB (Thread Control Block) in kernel memory
- ✅ PCB (Process Control Block) in kernel memory
- ✅ Never swapped - needed for fast scheduling
- ✅ ~1-2 KB per thread/process

### Systems Programming Insights
- ✅ Always protect shared data with locks
- ✅ RAII for lock management (lock_guard, unique_lock)
- ✅ Atomic operations for simple counters
- ✅ Cache coherency matters on multi-core systems
