# Process, Threads & Concurrency

## Systems Programmer Perspective

Understanding concurrency is critical for:
- Writing high-performance applications
- Understanding OS internals
- Debugging race conditions and deadlocks
- Efficient resource utilization

## Learning Path

### Part 1: Process vs Thread Fundamentals
- Memory layout (stack, heap, code, data segments)
- Context switching costs
- When to use processes vs threads

### Part 2: Thread Basics (std::thread)
- Creating and managing threads
- join() vs detach()
- Thread lifecycle
- Passing arguments to threads

### Part 3: Synchronization Primitives
- std::mutex and lock_guard
- std::condition_variable
- std::atomic types
- Memory ordering

### Part 4: Common Concurrency Problems
- Race conditions
- Deadlocks
- Starvation
- Priority inversion

### Part 5: Concurrency Patterns
- Thread pool
- Producer-Consumer
- Reader-Writer
- Future/Promise

### Part 6: Real-world Examples
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

## Key Takeaways (will update as we progress)
- Threads share memory → faster but need synchronization
- Processes isolated → safer but higher overhead
- Always protect shared data with locks
- RAII for lock management (lock_guard, unique_lock)
- Atomic operations for simple counters
