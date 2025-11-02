#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// =================================================================================
// Part 10: Private Inheritance Example
// =================================================================================

/*
 * SCENARIO: We have a library `Timer` class. We want to build a `ConnectionManager`
 * that periodically checks for stale connections. We want to USE the timer's
 * capability but HIDE its interface from the outside world.
 *
 * WHY PRIVATE INHERITANCE?
 * 1. Implementation Reuse: We want the timer's logic.
 * 2. Interface Hiding: We do NOT want users of `ConnectionManager` to be able
 *    to call `start()` or `stop()` on it. All public members of `Timer` become
 *    PRIVATE in `ConnectionManager`.
 * 3. Virtual Function Override: This is the key reason. We need to provide our
 *    own implementation for the `virtual void onTick()`. This is not possible
 *    with composition alone.
 */

// --- Library Class (Imagine this is from a 3rd party) ---
class Timer {
private:
    bool m_running = false;
    std::chrono::seconds m_interval;

public:
    Timer(int interval_seconds) : m_interval(interval_seconds) {}

    void start() {
        m_running = true;
        std::cout << "[Timer]: Starting timer with " << m_interval.count() << "s interval." << std::endl;
        // In a real system, this would spawn a thread. We'll simulate it.
        std::thread([this]() {
            while (m_running) {
                std::this_thread::sleep_for(m_interval);
                if (m_running) {
                    this->onTick(); // Polymorphic call!
                }
            }
        }).detach();
    }

    void stop() {
        std::cout << "[Timer]: Stopping timer." << std::endl;
        m_running = false;
    }

    virtual void onTick() {
        std::cout << "[Timer]: Default tick." << std::endl;
    }

    virtual ~Timer() = default;
};


// --- Our Implementation using Private Inheritance ---
// `ConnectionManager` IS-IMPLEMENTED-IN-TERMS-OF a `Timer`.
// It is NOT a `Timer` from the outside world's perspective.
class ConnectionManager : private Timer {
public:
    ConnectionManager() : Timer(5) { // We initialize the base Timer with a 5s interval
        // The public interface of Timer (start, stop) is now PRIVATE to ConnectionManager.
    }

    // We provide a new public interface that is relevant to our class.
    void beginMonitoring() {
        std::cout << "[ConnectionManager]: Starting to monitor connections." << std::endl;
        start(); // We can call the base class's public methods from within.
    }

    void shutdown() {
        std::cout << "[ConnectionManager]: Shutting down connection monitoring." << std::endl;
        stop(); // We can call the base class's public methods from within.
    }

private:
    // Here we override the virtual function to provide our specific logic.
    // This is the main reason we chose inheritance over composition.
    void onTick() override {
        std::cout << "[ConnectionManager]: Checking for stale connections..." << std::endl;
        // ... logic to ping connections and clean up would go here ...
    }
};


int main() {
    std::cout << "--- Demonstrating Private Inheritance ---" << std::endl;
    ConnectionManager manager;

    // 1. The public interface is clean and specific to ConnectionManager.
    manager.beginMonitoring();

    // manager.start(); // COMPILE ERROR! 'start' is a private member of 'ConnectionManager'
    // Timer* t_ptr = &manager; // COMPILE ERROR! 'Timer' is an inaccessible base of 'ConnectionManager'

    std::cout << "\nSystem will run for 12 seconds to see a couple of ticks..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(12));

    // 2. The shutdown is also controlled via our own interface.
    manager.shutdown();
    std::cout << "\nShutdown complete." << std::endl;
    
    // Allow the background thread to terminate gracefully
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
