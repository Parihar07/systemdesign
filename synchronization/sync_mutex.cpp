#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
// Define a large number of iterations to make the race condition more likely
const int ITERATIONS = 100000;
std::mutex mtx;
/**
 * @brief WORKER 1: The Unsafe Implementation (Causes Race Condition)
 * PROS:
 *  - Fast: No locking overhead.
 * CONS:
 *  - COMPLETELY THREAD-UNSAFE.
 *  - Produces incorrect, non-deterministic results due to data races.
 *  - Fundamentally broken for concurrent access to shared data.
 */
void workFun(int &so)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        so += 2;
    }
}

/**
 * @brief WORKER 2: Manual Lock and Unlock
 * PROS:
 *  - Correctly solves the race condition and produces the right result.
 *  - Demonstrates the fundamental lock/unlock mechanism of a mutex.
 * CONS:
 *  - NOT EXCEPTION-SAFE: If an exception occurs after mtx.lock(), mtx.unlock()
 *    will never be called, causing a permanent deadlock.
 *  - Error-prone: The programmer might forget to call unlock() on all code paths.
 */
void safeWorker(int &so)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        // Lock the mutex just before accessing the shared data
        mtx.lock();

        // This is the critical section - only one thread can be here at a time
        so += 2;

        // Unlock the mutex immediately after the critical section is done
        mtx.unlock();
    }
}

/**
 * @brief WORKER 3: RAII with std::lock_guard (The Modern C++ Way)
 * PROS:
 *  - Correctly solves the race condition.
 *  - EXCEPTION-SAFE: The lock is automatically released when the `lock_guard`
 *    object goes out of scope, no matter how. This prevents deadlocks.
 *  - Less error-prone: You cannot forget to unlock the mutex.
 *  - Cleaner and more concise code.
 * CONS:
 *  - `lock_guard` is simple and not as flexible as `std::unique_lock` for advanced scenarios.
 */
void safeWorkerRAII(int &so)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        lock_guard<mutex> protect(mtx);
        // This is the critical section - only one thread can be here at a time
        so += 2;
    }
}

int main()
{
    cout << "--- Solving Race Condition with std::lock_guard (RAII) ---" << endl;

    // This integer is the shared resource
    int so = 23;

    // Create two threads that both run workFun, modifying the shared 'so'
    thread t1(safeWorkerRAII, std::ref(so));
    thread t2(safeWorkerRAII, std::ref(so));

    // Wait for both threads to complete their execution
    t1.join();
    t2.join();

    // Calculate and display the expected vs. actual results
    int expected_so = 23 + (2 * ITERATIONS * 2);
    cout << "Expected final value: " << expected_so << endl;
    cout << "Actual final value:   " << so << endl;
    cout << "\nThe actual value is correct and the code is exception-safe due to RAII!" << endl;

    return 0;
}