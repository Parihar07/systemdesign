/**
 * Part 1: Process vs Thread Fundamentals
 * 
 * SYSTEMS PROGRAMMER PERSPECTIVE:
 * ================================
 * 
 * PROCESS:
 * - Independent execution unit with its own memory space
 * - Has its own: Code, Data, Heap, Stack segments
 * - OS allocates separate virtual address space
 * - Context switch: Save/restore ALL registers, page tables, TLB flush
 * - Inter-process communication: Pipes, shared memory, sockets (expensive)
 * 
 * THREAD:
 * - Lightweight execution unit within a process
 * - Shares: Code, Data, Heap segments with other threads
 * - Has own: Stack, registers (PC, SP), thread-local storage
 * - Context switch: Save/restore only registers and stack pointer (cheaper)
 * - Communication: Direct memory access (shared variables)
 * 
 * MEMORY LAYOUT:
 * 
 * Process Memory:          Thread Memory (same process):
 * +----------------+       +----------------+
 * | Kernel Space   |       | Kernel Space   |
 * +----------------+       +----------------+
 * | Stack (grows ↓)|       | Stack Thread 1 | ← Each thread has own stack
 * |                |       | Stack Thread 2 |
 * |                |       | Stack Thread 3 |
 * +----------------+       +----------------+
 * | Heap (grows ↑) |       | Heap (SHARED)  | ← All threads share heap
 * +----------------+       +----------------+
 * | Data (globals) |       | Data (SHARED)  | ← All threads share globals
 * +----------------+       +----------------+
 * | Code (text)    |       | Code (SHARED)  | ← All threads share code
 * +----------------+       +----------------+
 * 
 * CONTEXT SWITCH COST (approximate):
 * - Thread context switch: 1-2 microseconds
 * - Process context switch: 10-20 microseconds (TLB flush, page table reload)
 */

#include <iostream>
#include <thread>
#include <unistd.h>     // for fork(), getpid()
#include <sys/wait.h>   // for wait()
#include <chrono>
#include <vector>

using namespace std;

// Global variable - shared across threads, NOT across processes
int global_counter = 0;

void thread_function(int thread_id) {
    cout << "Thread " << thread_id << " starting..." << endl;
    cout << "  PID: " << getpid() << endl;
    cout << "  Thread ID: " << this_thread::get_id() << endl;
    
    // Threads can directly access and modify global variables
    global_counter++;
    cout << "  Thread " << thread_id << " incremented global_counter to: " 
         << global_counter << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Thread " << thread_id << " finished" << endl;
}

void demonstrate_threads() {
    cout << "\n=== THREAD DEMONSTRATION ===" << endl;
    cout << "Main PID: " << getpid() << endl;
    cout << "Initial global_counter: " << global_counter << endl;
    
    vector<thread> threads;
    
    // Create 3 threads
    for(int i = 0; i < 3; i++) {
        threads.push_back(thread(thread_function, i));
    }
    
    // Wait for all threads to complete
    for(auto& t : threads) {
        t.join();
    }
    
    cout << "Final global_counter: " << global_counter << endl;
    cout << "All threads share same memory space!" << endl;
}

void demonstrate_processes() {
    cout << "\n=== PROCESS DEMONSTRATION ===" << endl;
    cout << "Parent PID: " << getpid() << endl;
    cout << "Initial global_counter: " << global_counter << endl;
    
    // Create 3 child processes
    for(int i = 0; i < 3; i++) {
        pid_t pid = fork();
        
        if(pid == 0) {
            // Child process
            cout << "Child process " << i << " starting..." << endl;
            cout << "  PID: " << getpid() << endl;
            cout << "  Parent PID: " << getppid() << endl;
            
            // Each process has its own copy of global_counter
            global_counter++;
            cout << "  Child " << i << " incremented global_counter to: " 
                 << global_counter << endl;
            
            // Child must exit, otherwise it will continue loop
            exit(0);
        }
        else if(pid < 0) {
            cerr << "Fork failed!" << endl;
        }
        // Parent continues loop to create more children
    }
    
    // Parent waits for all children
    for(int i = 0; i < 3; i++) {
        wait(NULL);
    }
    
    cout << "Parent final global_counter: " << global_counter << endl;
    cout << "Each process has its own memory space!" << endl;
}

void compare_performance() {
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    
    // Thread creation time
    auto start = chrono::high_resolution_clock::now();
    vector<thread> threads;
    for(int i = 0; i < 100; i++) {
        threads.push_back(thread([](){
            // Do minimal work
            volatile int x = 0;
            x++;
        }));
    }
    for(auto& t : threads) {
        t.join();
    }
    auto end = chrono::high_resolution_clock::now();
    auto thread_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Creating/joining 100 threads: " << thread_time.count() << " μs" << endl;
    cout << "Average per thread: " << thread_time.count() / 100.0 << " μs" << endl;
    
    // Process creation is much slower - don't create 100!
    // Just demonstrating the concept
    cout << "\nNote: Process creation is ~10x slower" << endl;
    cout << "fork() involves copying page tables, setting up new address space" << endl;
}

int main() {
    cout << "PROCESS vs THREAD: Systems Programmer View" << endl;
    cout << "==========================================" << endl;
    
    // Demonstrate threads
    demonstrate_threads();
    
    // Reset counter
    global_counter = 0;
    
    // Demonstrate processes
    demonstrate_processes();
    
    // Performance comparison
    compare_performance();
    
    cout << "\n=== KEY TAKEAWAYS ===" << endl;
    cout << "1. Threads share memory (code, data, heap) - faster IPC" << endl;
    cout << "2. Processes isolated - safer but higher overhead" << endl;
    cout << "3. Thread context switch ~10x faster than process" << endl;
    cout << "4. Use threads when: Need fast IPC, shared state" << endl;
    cout << "5. Use processes when: Need isolation, security, stability" << endl;
    
    return 0;
}
