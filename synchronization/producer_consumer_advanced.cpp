// Advanced Producer-Consumer Example: Multiple Producers and Consumers
// Demonstrates use of std::condition_variable, std::mutex, and safe shutdown for multiple threads.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
queue<int> data_queue;
bool finished_producing = false;
const int NUM_PRODUCERS = 2;
const int NUM_CONSUMERS = 3;
const int ITEMS_PER_PRODUCER = 5;

void producer(int id)
{
    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(100 + 50 * id));
        lock_guard<mutex> lock(mtx);
        int value = id * 100 + i;
        cout << "Producer " << id << " pushing: " << value << endl;
        data_queue.push(value);
        cv.notify_one();
    }
    // Atomically update producer count and signal shutdown if all are done
    {
        lock_guard<mutex> lock(mtx);
        static int producers_done = 0;
        if (++producers_done == NUM_PRODUCERS)
        {
            cout << "Last producer (" << id << ") finished. Signaling all consumers to shutdown." << endl;
            finished_producing = true;
            cv.notify_all();
        }
    }
}
void consumer(int id)
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []
                { return !data_queue.empty() || finished_producing; });
        if (!data_queue.empty())
        {
            int data = data_queue.front();
            data_queue.pop();
            lock.unlock();
            cout << "    Consumer " << id << " processed: " << data << endl;
        }
        else if (finished_producing)
        {
            cout << "Consumer " << id << " finished." << endl;
            break;
        }
    }
}

int main()
{
    cout << "--- Advanced Producer-Consumer: Multiple Producers and Consumers ---" << endl;
    vector<thread> producers, consumers;
    for (int i = 0; i < NUM_PRODUCERS; ++i)
        producers.emplace_back(producer, i + 1);
    for (int i = 0; i < NUM_CONSUMERS; ++i)
        consumers.emplace_back(consumer, i + 1);
    for (auto &t : producers)
        t.join();
    for (auto &t : consumers)
        t.join();
    cout << "\nAll threads finished. Program complete." << endl;
    return 0;
}
