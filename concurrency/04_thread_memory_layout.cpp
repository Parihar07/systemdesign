/**
 * Thread Memory Layout - Systems Programmer Deep Dive
 * 
 * CRITICAL UNDERSTANDING:
 * ======================
 * Threads DON'T have separate memory layouts like processes!
 * All threads in a process SHARE the same address space.
 * 
 * What makes each thread "independent":
 * 1. Each thread has its own STACK (carved from shared address space)
 * 2. Each thread has its own CPU register state (saved in Thread Control Block)
 * 3. Each thread has Thread Local Storage (TLS) - optional per-thread data
 * 
 * MEMORY LAYOUT VISUALIZATION:
 * ============================
 * 
 * Single Process (1 Thread):          Multi-Threaded Process (3 Threads):
 * 
 * ┌─────────────────────┐             ┌─────────────────────┐
 * │   Kernel Space      │             │   Kernel Space      │
 * ├─────────────────────┤             ├─────────────────────┤
 * │                     │             │   Stack Thread 1    │ ← 8MB (default)
 * │   Stack (grows ↓)   │             ├─────────────────────┤
 * │        8MB          │             │   Stack Thread 2    │ ← 8MB
 * │                     │             ├─────────────────────┤
 * │                     │             │   Stack Thread 3    │ ← 8MB
 * ├─────────────────────┤             ├─────────────────────┤
 * │   Memory Mapping    │             │   Memory Mapping    │
 * │   (mmap, libs)      │             │   (mmap, libs)      │ ← SAME for all threads
 * ├─────────────────────┤             ├─────────────────────┤
 * │                     │             │                     │
 * │   Heap (grows ↑)    │             │   Heap (grows ↑)    │ ← SHARED by all threads!
 * │                     │             │                     │
 * ├─────────────────────┤             ├─────────────────────┤
 * │   BSS (uninit)      │             │   BSS (uninit)      │ ← SHARED
 * ├─────────────────────┤             ├─────────────────────┤
 * │   Data (globals)    │             │   Data (globals)    │ ← SHARED
 * ├─────────────────────┤             ├─────────────────────┤
 * │   Text (code)       │             │   Text (code)       │ ← SHARED
 * └─────────────────────┘             └─────────────────────┘
 * 
 * KEY INSIGHT: 
 * - Process creates one big address space
 * - Each thread gets its own STACK region within that space
 * - Everything else (heap, globals, code) is SHARED
 * 
 * THREAD CONTROL BLOCK (TCB):
 * ===========================
 * OS maintains a TCB for each thread (not in process address space!):
 * 
 * struct thread_control_block {
 *     // CPU Register State (saved during context switch)
 *     uint64_t rax, rbx, rcx, rdx;  // General purpose
 *     uint64_t rsi, rdi, rbp, rsp;  // Stack/base pointers
 *     uint64_t r8, r9, ..., r15;    // Extended registers
 *     uint64_t rip;                 // Instruction pointer
 *     uint64_t rflags;              // CPU flags
 *     
 *     // Thread-specific info
 *     void* stack_base;             // Bottom of stack
 *     size_t stack_size;            // Usually 8MB
 *     int thread_id;                // TID
 *     int priority;
 *     int state;                    // Running, blocked, ready
 *     
 *     // Thread Local Storage
 *     void* tls_base;               // Points to TLS area
 * };
 */

#include <iostream>
#include <thread>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <sys/resource.h>

using namespace std;

// Global variable - in DATA segment, SHARED by all threads
int global_var = 100;

// Thread Local Storage - each thread has own copy
thread_local int tls_var = 0;

void print_memory_layout(int thread_id) {
    // Local variable - on THIS thread's stack
    int local_var = thread_id;
    
    // Heap allocation - from SHARED heap
    int* heap_var = new int(thread_id * 10);
    
    // Get stack size limit
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    
    cout << "\n=== Thread " << thread_id << " Memory Map ===" << endl;
    cout << "Thread ID (TID): " << this_thread::get_id() << endl;
    cout << "Process ID (PID): " << getpid() << " (same for all threads)" << endl;
    
    // Addresses are in virtual memory space
    cout << "\nMemory Addresses (Virtual):" << endl;
    cout << "  Local var (stack):   " << &local_var 
         << " [Thread's own stack]" << endl;
    cout << "  Heap allocation:     " << heap_var 
         << " [SHARED heap]" << endl;
    cout << "  Global var:          " << &global_var 
         << " [SHARED data segment]" << endl;
    cout << "  Thread-local var:    " << &tls_var 
         << " [Thread's own TLS]" << endl;
    cout << "  Function code:       " << (void*)&print_memory_layout 
         << " [SHARED code segment]" << endl;
    
    cout << "\nStack Info:" << endl;
    cout << "  Stack size limit: " << limit.rlim_cur / (1024*1024) << " MB" << endl;
    
    // Modify thread-local variable
    tls_var = thread_id * 100;
    cout << "  TLS value: " << tls_var << " (independent per thread)" << endl;
    
    delete heap_var;
}

void demonstrate_shared_vs_separate() {
    cout << "\n=== DEMONSTRATING SHARED vs SEPARATE ===" << endl;
    
    // Allocate on heap - will be shared
    int* shared_heap = new int(42);
    cout << "Main: Created heap variable at " << shared_heap 
         << " with value " << *shared_heap << endl;
    
    thread t1([shared_heap]() {
        cout << "Thread 1: Can access same heap address " << shared_heap << endl;
        cout << "Thread 1: Value = " << *shared_heap << endl;
        *shared_heap = 99;  // Modify it
        cout << "Thread 1: Changed to 99" << endl;
    });
    
    t1.join();
    
    cout << "Main: After thread, value = " << *shared_heap 
         << " (modified by thread!)" << endl;
    
    delete shared_heap;
}

void demonstrate_stack_independence() {
    cout << "\n=== STACK INDEPENDENCE ===" << endl;
    
    // Each thread's local variables are on different stacks
    auto worker = [](int id) {
        // This variable is on this thread's stack
        int stack_array[1000];
        stack_array[0] = id;
        
        cout << "Thread " << id << " stack array at: " 
             << &stack_array[0] << endl;
        cout << "Thread " << id << " stack pointer (approx): " 
             << &id << endl;
        
        // Calculate rough stack position
        // On Linux x86-64, stacks grow downward
        size_t stack_addr = (size_t)&stack_array[0];
        cout << "Thread " << id << " stack address: 0x" 
             << hex << stack_addr << dec << endl;
    };
    
    vector<thread> threads;
    for(int i = 0; i < 3; i++) {
        threads.push_back(thread(worker, i));
    }
    
    for(auto& t : threads) {
        t.join();
    }
    
    cout << "\nNotice: Each thread's stack is at different address!" << endl;
    cout << "These are separate 8MB regions in same address space" << endl;
}

void demonstrate_tls() {
    cout << "\n=== THREAD LOCAL STORAGE (TLS) ===" << endl;
    
    // Set TLS in main thread
    tls_var = 999;
    cout << "Main thread: tls_var = " << tls_var 
         << " at address " << &tls_var << endl;
    
    auto worker = [](int id) {
        // Each thread sees its own tls_var
        cout << "Thread " << id << ": Initial tls_var = " << tls_var 
             << " at address " << &tls_var << endl;
        
        tls_var = id * 1000;
        
        cout << "Thread " << id << ": Set tls_var = " << tls_var << endl;
    };
    
    vector<thread> threads;
    for(int i = 1; i <= 3; i++) {
        threads.push_back(thread(worker, i));
    }
    
    for(auto& t : threads) {
        t.join();
    }
    
    cout << "Main thread: tls_var still = " << tls_var 
         << " (unchanged!)" << endl;
    cout << "\nTLS provides per-thread variables without locking!" << endl;
}

void show_actual_stack_usage() {
    cout << "\n=== ACTUAL STACK USAGE ===" << endl;
    
    auto recursive_func = [](auto& self, int depth, void* initial_sp) -> void {
        char buffer[100];  // Allocate on stack
        
        if(depth == 0) {
            void* current_sp = &buffer;
            size_t stack_used = (char*)initial_sp - (char*)current_sp;
            cout << "  Stack used in recursion: " << stack_used << " bytes" << endl;
            return;
        }
        
        self(self, depth - 1, initial_sp);
    };
    
    thread t([&recursive_func]() {
        char marker;
        void* initial_sp = &marker;
        cout << "Thread starting, stack pointer at: " << initial_sp << endl;
        
        recursive_func(recursive_func, 100, initial_sp);
    });
    
    t.join();
    
    cout << "Each recursion used ~100 bytes (local variables + return address)" << endl;
}

int main() {
    cout << "THREAD MEMORY LAYOUT - DEEP DIVE" << endl;
    cout << "===================================" << endl;
    
    // Create multiple threads and show their memory maps
    vector<thread> threads;
    for(int i = 1; i <= 3; i++) {
        threads.push_back(thread(print_memory_layout, i));
    }
    
    for(auto& t : threads) {
        t.join();
    }
    
    // Show what's shared vs separate
    demonstrate_shared_vs_separate();
    
    // Show stack independence
    demonstrate_stack_independence();
    
    // Show thread-local storage
    demonstrate_tls();
    
    // Show actual stack usage
    show_actual_stack_usage();
    
    cout << "\n=== SUMMARY: THREAD MEMORY MODEL ===" << endl;
    cout << "┌─────────────────────────────────────────────┐" << endl;
    cout << "│ SHARED (All threads see same memory):      │" << endl;
    cout << "│  ✓ Heap (malloc/new)                       │" << endl;
    cout << "│  ✓ Global variables                        │" << endl;
    cout << "│  ✓ Static variables                        │" << endl;
    cout << "│  ✓ Code (functions)                        │" << endl;
    cout << "│  ✓ File descriptors                        │" << endl;
    cout << "│  ✓ Memory mapped regions                   │" << endl;
    cout << "├─────────────────────────────────────────────┤" << endl;
    cout << "│ SEPARATE (Each thread has own):            │" << endl;
    cout << "│  ✓ Stack (8MB default)                     │" << endl;
    cout << "│  ✓ CPU Registers (saved in TCB)            │" << endl;
    cout << "│  ✓ Thread Local Storage (thread_local)     │" << endl;
    cout << "│  ✓ Signal mask (can be different)          │" << endl;
    cout << "│  ✓ Thread ID (TID)                         │" << endl;
    cout << "└─────────────────────────────────────────────┘" << endl;
    
    cout << "\nKey Insight for Systems Programmers:" << endl;
    cout << "Threads don't have 'separate memory layouts' like processes." << endl;
    cout << "They're execution contexts WITHIN the same address space!" << endl;
    cout << "Think: Multiple instruction pointers (RIP) wandering through" << endl;
    cout << "      the same memory, each with its own stack." << endl;
    
    return 0;
}
