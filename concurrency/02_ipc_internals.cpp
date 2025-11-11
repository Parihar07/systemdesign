/**
 * Part 2: Process Internals & Communication Mechanisms
 * 
 * SYSTEMS PROGRAMMER PERSPECTIVE:
 * ================================
 * 
 * INTRA-PROCESS COMMUNICATION (Between threads in SAME process):
 * ---------------------------------------------------------------
 * - Shared Memory: Direct access to global/heap variables
 * - Fastest: Just memory load/store instructions
 * - Problem: Need synchronization (mutex, atomic) to avoid race conditions
 * - Cost: ~1-2 CPU cycles for memory access
 * 
 * INTER-PROCESS COMMUNICATION (Between DIFFERENT processes):
 * -----------------------------------------------------------
 * 1. Pipes: Unidirectional byte stream, kernel buffered
 *    - Cost: System call overhead + kernel buffer copy
 * 
 * 2. Shared Memory: Separate processes map same physical memory
 *    - Fastest IPC between processes
 *    - Still needs synchronization (semaphores, futex)
 *    - Cost: ~100 CPU cycles for setup, then direct memory access
 * 
 * 3. Message Queues: Kernel-managed message passing
 *    - Cost: System call + kernel copy
 * 
 * 4. Sockets: Network-style communication (even on same machine)
 *    - Cost: Highest overhead, protocol stack processing
 * 
 * MEMORY ACCESS PERSPECTIVE:
 * ==========================
 * 
 * Thread accessing shared variable:
 * CPU → L1 Cache → L2 Cache → L3 Cache → RAM → Variable
 * Cost: 1-200 CPU cycles (depending on cache hit/miss)
 * 
 * Process A sending to Process B via pipe:
 * CPU → syscall → kernel space → copy to pipe buffer → 
 * context switch → Process B → syscall → copy from pipe → user space
 * Cost: 1000-5000 CPU cycles + context switch
 * 
 * STACK vs HEAP for Thread Communication:
 * ========================================
 * Stack: Each thread has own stack (8MB default on Linux)
 *        - Cannot share stack variables between threads safely
 *        - Stack pointer (SP) is per-thread
 * 
 * Heap:  All threads share same heap
 *        - malloc/new allocates from shared heap
 *        - Perfect for thread communication
 *        - Need synchronization for concurrent access
 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
#include <cstring>

// POSIX IPC headers (for inter-process communication)
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>   // for shared memory
#include <fcntl.h>

using namespace std;

// ==================================================================
// PART 1: INTRA-PROCESS COMMUNICATION (Threads)
// ==================================================================

// Global variable - in data segment, shared by all threads
int shared_global = 0;
mutex global_mutex;

// Heap-allocated shared data
struct SharedData {
    int counter;
    char message[100];
    
    SharedData() : counter(0) {
        strcpy(message, "Initial message");
    }
};

void thread_worker(int id, SharedData* shared) {
    // This function executes in thread's own stack
    // But 'shared' points to heap memory accessible by all threads
    
    cout << "Thread " << id << " - Stack address of 'id': " 
         << &id << endl;  // Each thread has different stack
    
    // Accessing shared heap data
    {
        lock_guard<mutex> lock(global_mutex);
        shared->counter++;
        cout << "Thread " << id << " incremented counter to: " 
             << shared->counter << endl;
    }
    
    // Accessing shared global
    {
        lock_guard<mutex> lock(global_mutex);
        shared_global += 10;
        cout << "Thread " << id << " incremented global to: " 
             << shared_global << endl;
    }
}

void demonstrate_intra_process_communication() {
    cout << "\n=== INTRA-PROCESS COMMUNICATION (Threads) ===" << endl;
    cout << "Mechanism: Direct memory access (shared heap/globals)" << endl;
    
    // Allocate shared data on heap
    SharedData* shared = new SharedData();
    cout << "Shared data address (heap): " << shared << endl;
    
    vector<thread> threads;
    
    // Create threads - all share same heap
    for(int i = 0; i < 5; i++) {
        threads.push_back(thread(thread_worker, i, shared));
    }
    
    for(auto& t : threads) {
        t.join();
    }
    
    cout << "Final counter: " << shared->counter << endl;
    cout << "Final global: " << shared_global << endl;
    cout << "Communication cost: ~1-200 CPU cycles (memory access)" << endl;
    
    delete shared;
}

// ==================================================================
// PART 2: INTER-PROCESS COMMUNICATION (Processes)
// ==================================================================

void demonstrate_pipe_ipc() {
    cout << "\n=== INTER-PROCESS: PIPE IPC ===" << endl;
    
    int pipefd[2];  // pipefd[0] = read end, pipefd[1] = write end
    
    if(pipe(pipefd) == -1) {
        cerr << "Pipe creation failed!" << endl;
        return;
    }
    
    pid_t pid = fork();
    
    if(pid == 0) {
        // Child process - WRITER
        close(pipefd[0]);  // Close read end
        
        const char* msg = "Hello from child process!";
        cout << "Child (PID " << getpid() << ") writing to pipe..." << endl;
        
        // Write to pipe - this involves:
        // 1. System call (user → kernel mode)
        // 2. Copy data to kernel pipe buffer
        // 3. Wake up reader if waiting
        write(pipefd[1], msg, strlen(msg) + 1);
        
        close(pipefd[1]);
        exit(0);
    }
    else {
        // Parent process - READER
        close(pipefd[1]);  // Close write end
        
        char buffer[100];
        cout << "Parent (PID " << getpid() << ") reading from pipe..." << endl;
        
        // Read from pipe - this involves:
        // 1. System call (user → kernel mode)
        // 2. Copy data from kernel pipe buffer
        // 3. Block if no data available
        read(pipefd[0], buffer, sizeof(buffer));
        
        cout << "Parent received: " << buffer << endl;
        
        close(pipefd[0]);
        wait(NULL);  // Wait for child to exit
    }
    
    cout << "Communication cost: ~1000-5000 CPU cycles (syscall + copy)" << endl;
}

void demonstrate_shared_memory_ipc() {
    cout << "\n=== INTER-PROCESS: SHARED MEMORY ===" << endl;
    
    // Create shared memory region
    // mmap with MAP_SHARED | MAP_ANONYMOUS creates memory shared between processes
    int* shared_mem = (int*)mmap(NULL, sizeof(int), 
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS, 
                                  -1, 0);
    
    if(shared_mem == MAP_FAILED) {
        cerr << "mmap failed!" << endl;
        return;
    }
    
    *shared_mem = 0;  // Initialize
    cout << "Shared memory address: " << shared_mem << endl;
    
    pid_t pid = fork();
    
    if(pid == 0) {
        // Child process
        cout << "Child (PID " << getpid() << ") accessing shared memory..." << endl;
        
        // Child can directly access shared memory
        // No system call needed after setup!
        for(int i = 0; i < 5; i++) {
            (*shared_mem)++;
            cout << "  Child incremented to: " << *shared_mem << endl;
            usleep(100000);  // 100ms
        }
        
        exit(0);
    }
    else {
        // Parent process
        cout << "Parent (PID " << getpid() << ") waiting and monitoring..." << endl;
        
        // Parent can also access shared memory
        usleep(600000);  // Wait for child to finish
        
        cout << "Parent sees final value: " << *shared_mem << endl;
        
        wait(NULL);
        munmap(shared_mem, sizeof(int));  // Cleanup
    }
    
    cout << "Communication cost: ~100 cycles (setup) + direct memory access" << endl;
}

// ==================================================================
// PART 3: PERFORMANCE COMPARISON
// ==================================================================

void performance_comparison() {
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    
    // Measure intra-process (thread) communication
    atomic<int> thread_counter{0};
    
    auto start = chrono::high_resolution_clock::now();
    
    vector<thread> threads;
    for(int i = 0; i < 1000; i++) {
        threads.push_back(thread([&thread_counter]() {
            thread_counter++;  // Atomic operation, ~10-20 cycles
        }));
    }
    for(auto& t : threads) {
        t.join();
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto thread_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "1000 thread communications (atomic inc): " 
         << thread_time.count() << " μs" << endl;
    cout << "Average: " << thread_time.count() / 1000.0 << " μs per operation" << endl;
    
    // Pipe communication is much slower (~1000x)
    cout << "\nPipe/Socket IPC: ~1-10 μs per message (system call overhead)" << endl;
    cout << "Shared memory IPC: ~0.01-0.1 μs (after setup)" << endl;
}

int main() {
    cout << "PROCESS INTERNALS & IPC MECHANISMS" << endl;
    cout << "====================================" << endl;
    
    // Intra-process: Threads share memory
    demonstrate_intra_process_communication();
    
    // Inter-process: Pipe
    demonstrate_pipe_ipc();
    
    // Inter-process: Shared memory
    demonstrate_shared_memory_ipc();
    
    // Performance comparison
    performance_comparison();
    
    cout << "\n=== KEY TAKEAWAYS ===" << endl;
    cout << "1. INTRA-PROCESS (threads):" << endl;
    cout << "   - Share: heap, globals, code, file descriptors" << endl;
    cout << "   - Separate: stack (each thread has own stack)" << endl;
    cout << "   - Communication: Direct memory access (fastest)" << endl;
    cout << "   - Cost: 1-200 CPU cycles (cache dependent)" << endl;
    
    cout << "\n2. INTER-PROCESS:" << endl;
    cout << "   - Isolated address spaces" << endl;
    cout << "   - Pipe/Socket: System call + kernel copy (~1000 cycles)" << endl;
    cout << "   - Shared Memory: Setup overhead + direct access (~100 cycles)" << endl;
    cout << "   - Message Queue: System call + queuing overhead" << endl;
    
    cout << "\n3. WHEN TO USE:" << endl;
    cout << "   - Threads: Performance critical, shared state needed" << endl;
    cout << "   - Processes: Isolation, security, fault tolerance" << endl;
    cout << "   - Shared Memory IPC: Fast IPC between processes" << endl;
    cout << "   - Pipe/Socket: Simple, portable, safe communication" << endl;
    
    return 0;
}
