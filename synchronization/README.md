# Synchronization in C++

This directory contains examples and explanations of synchronization primitives and patterns in C++.

## Topics Covered

- Mutexes and lock guards
- Condition variables
- Producer-consumer (single and multiple threads)
- Atomics and lock-free programming
- Semaphores (manual and C++20)

---

### Semaphore Examples

**Problem Statement:**
Limit the number of threads that can access a resource or section of code at the same time (e.g., connection pool, thread pool). Demonstrate with both a portable implementation and C++20's std::counting_semaphore.

- `semaphore_native.cpp`: Manual semaphore using mutex and condition_variable (portable, C++11+)
- `semaphore_cpp20.cpp`: C++20 std::counting_semaphore (if supported by your compiler), with fallback to portable version

**Usage:**
- If your compiler does not support `<semaphore>`, use the portable version by uncommenting the provided class in `semaphore_cpp20.cpp`.
- Both versions provide the same acquire/release API for limiting concurrency.

---

See code comments for detailed explanations and usage instructions.
