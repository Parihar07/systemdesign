
// =============================================
// Semaphore Example: Limiting Concurrency in C++
// =============================================
// Problem Statement:
//   Implement a resource pool (e.g., connection pool) where only a fixed number
//   of threads (e.g., 3) can access the resource at the same time. All other threads
//   must wait until a slot is available. Demonstrate this using a semaphore.
//
// This file shows two approaches:
//   1. C++20 std::counting_semaphore (if supported by your compiler)
//   2. A portable implementation using mutex and condition_variable (uncomment to use)
//
// Usage Note:
//   - If your compiler does not support <semaphore>, use the portable CountingSemaphore class.
//   - Both versions provide acquire()/release() methods for limiting concurrency.
//
// See the project README for more details.

#include <iostream>
#include <thread>
// #include <semaphore>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
using namespace std;
// Portable counting semaphore implementation
class CountingSemaphore
{
    int count;
    std::mutex mtx;
    std::condition_variable cv;

public:
    CountingSemaphore(int initial) : count(initial) {}
    void acquire()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]
                { return count > 0; });
        --count;
    }
    void release()
    {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

CountingSemaphore sem(3);
// Create a counting semaphore with 3 available slots
// std::counting_semaphore<3> sem(3);

void worker(int id)
{
    sem.acquire(); // Wait for a slot
    cout << "Thread " << id << " entered\n";
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout << "Thread " << id << " leaving\n";
    sem.release(); // Release the slot
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.emplace_back(worker, i);
    for (auto &t : threads)
        t.join();
    return 0;
}
