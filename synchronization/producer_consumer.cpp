#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

/*
 * THE PRODUCER-CONSUMER PROBLEM
 * ==============================
 * This example demonstrates why a condition_variable is essential for efficient
 * thread synchronization, which a mutex alone cannot provide.
 *
 * - A `mutex` is for MUTUAL EXCLUSION (protecting shared data).
 * - A `condition_variable` is for SYNCHRONIZATION (coordinating threads, waiting/notifying).
 *
 * SCENARIO:
 * - A "Producer" thread generates data and puts it into a shared queue.
 * - A "Consumer" thread takes data from the queue and processes it.
 *
 * THE PROBLEM A MUTEX ALONE CAN'T SOLVE:
 * What should the Consumer do if the queue is empty?
 * - Bad solution: Constantly lock, check if empty, unlock, and repeat. This is
 *   "busy-waiting" and wastes 100% of a CPU core.
 *
 * THE CONDITION VARIABLE SOLUTION:
 * The Consumer can "wait" on a condition variable, which puts the thread to sleep
 * (0% CPU usage) until the Producer "notifies" it that new data is available.
 */

// Shared resources
mutex mtx;
condition_variable cv;
queue<int> data_queue;
bool finished_producing = false;

/**
 * @brief The producer function.
 * Generates numbers and pushes them onto the queue.
 */
void producer()
{
    cout << "Producer starting..." << endl;
    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(200)); // Simulate work

        // A new lock_guard is created for EACH iteration of the loop.
        // It locks the mutex here.
        lock_guard<mutex> lock(mtx);
        cout << "  Producer pushing: " << i << endl;
        data_queue.push(i);

        // Notify ONE waiting consumer that there is data available.
        cv.notify_one();

        // At the end of each loop iteration, the 'lock' object goes out of scope,
        // its destructor is called, and the mutex is automatically UNLOCKED.
        // This allows the consumer to acquire the lock.
    }

    // The loop is finished, so the mutex is currently unlocked.
    // Signal that production is finished
    // We create a NEW, separate lock_guard to safely modify the 'finished_producing' flag.
    lock_guard<mutex> lock(mtx);
    cout << "Producer finished." << endl;
    finished_producing = true;
    cv.notify_all(); // Wake up all consumers to let them finish
}

/*
Predicate function basically will check if the queue has data or processing of producer is finished
*/

// Predicate lambda for consumer wait
/*
you can also write this with cpp syntax like
auto predict = [](){
    return !data_queue.empty() || finished_producing;
}
*/
auto predict()
{
    return !data_queue.empty() || finished_producing;
};

/**
 * @brief The consumer function.
 * Waits for data, then processes it.
 */
void consumer()
{
    cout << "Consumer starting..." << endl;
    while (true)
    {
        // We MUST use unique_lock here instead of lock_guard for two reasons:
        // 1. cv.wait() requires a unique_lock because it needs to be able to
        //    unlock the mutex while it waits, and re-lock it upon waking up.
        //    A lock_guard is too simple and cannot be unlocked temporarily.
        // 2. We want to call lock.unlock() manually after taking an item from the queue,
        //    to release the lock as early as possible. lock_guard does not have an .unlock() method.
        unique_lock<mutex> lock(mtx);

        // cv.wait() is the heart of the synchronization. It does three things:
        // 1. Manages the Lock: It atomically UNLOCKS the mutex and puts the thread to sleep.
        //    When woken, it re-LOCKS the mutex before returning.
        // 2. Checks for Data: It waits until the condition (predict) is true.
        //    The first part of the condition is `!data_queue.empty()`.
        // 3. Checks for Completion: The second part of the condition is `finished_producing`.
        //    This allows the consumer to wake up and terminate when the producer is done.
        cv.wait(lock, predict);

        // After cv.wait() returns, we know the condition `!data_queue.empty() || finished_producing` is true.
        // We now need this if/else if block to determine WHICH part of the condition is true.
        // This is not a redundant check; it's required to decide what to do next.
        if (!data_queue.empty())
        {
            int data = data_queue.front();
            data_queue.pop();
            lock.unlock(); // Unlock early, before processing
            cout << "    Consumer processed: " << data << endl;
        }
        else if (finished_producing)
        {
            // Queue is empty and producer is done, so we can exit.
            cout << "Consumer finished." << endl;
            break; // Exit the loop
        }
    }
}

int main()
{
    cout << "--- Producer-Consumer with std::condition_variable ---" << endl;

    thread t_producer(producer);
    thread t_consumer(consumer);

    t_producer.join();
    t_consumer.join();

    cout << "\nAll threads finished. Program complete." << endl;

    return 0;
}