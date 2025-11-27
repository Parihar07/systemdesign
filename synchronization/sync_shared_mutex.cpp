// sync_shared_mutex.cpp
// Demonstrates the use of std::shared_mutex for implementing a readers-writer lock.
// This allows for concurrent reads, improving performance in read-heavy scenarios.

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>          // For std::lock_guard
#include <shared_mutex>   // For std::shared_mutex and std::shared_lock
#include <chrono>

// Architectural Comment:
// std::shared_mutex is a synchronization primitive that allows multiple threads
// to have simultaneous read-only access to a resource, while still providing
// exclusive access for threads that need to write to it.
//
// System View:
// - When a thread requests a shared_lock (for reading): It will be granted if
//   no other thread holds an exclusive lock. Multiple threads can hold a
//   shared_lock concurrently.
// - When a thread requests a unique_lock (for writing): It will be granted only
//   when ALL locks (both shared and exclusive) have been released. It's an
//   exclusive grant.
//
// This is highly efficient for data structures that are read frequently but
// modified infrequently. It reduces contention compared to a std::mutex where
// every read would have to wait for other reads to complete.

class Telemetry {
public:
    Telemetry() : value(0) {}

    void write(int newValue) {
        // Exclusive lock for writing. No other readers or writers can proceed.
        std::lock_guard<std::shared_mutex> lock(sm_mutex);
        value = newValue;
        std::cout << "Thread " << std::this_thread::get_id() << " (Writer) updated value to: " << value << std::endl;
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    int read() const {
        // Shared lock for reading. Multiple readers can execute this concurrently.
        std::shared_lock<std::shared_mutex> lock(sm_mutex);
        std::cout << "Thread " << std::this_thread::get_id() << " (Reader) sees value: " << value << std::endl;
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return value;
    }

private:
    mutable std::shared_mutex sm_mutex;
    int value;
};

void reader_task(const Telemetry& telemetry) {
    for (int i = 0; i < 5; ++i) {
        telemetry.read();
    }
}

void writer_task(Telemetry& telemetry) {
    for (int i = 0; i < 3; ++i) {
        telemetry.write(i + 1);
    }
}

int main() {
    std::cout << "--- Readers-Writer Lock with std::shared_mutex ---" << std::endl;

    Telemetry shared_telemetry;
    std::vector<std::thread> threads;

    // Create multiple readers and a couple of writers
    threads.emplace_back(writer_task, std::ref(shared_telemetry));
    threads.emplace_back(reader_task, std::ref(shared_telemetry));
    threads.emplace_back(reader_task, std::ref(shared_telemetry));
    threads.emplace_back(writer_task, std::ref(shared_telemetry));
    threads.emplace_back(reader_task, std::ref(shared_telemetry));

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\nAll threads have finished execution." << std::endl;

    return 0;
}
