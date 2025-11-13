#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void say_hello() {
    cout << "[function] Hello from thread " << this_thread::get_id() << "\n";
}

void print_number(int x) {
    cout << "[function] Number: " << x << " (thread " << this_thread::get_id() << ")\n";
}

int main() {
    cout << "Thread creation basics\n";
    cout << "Main thread id: " << this_thread::get_id() << "\n";

    // 1) Start thread with a free function
    thread t1(say_hello);

    // 2) Start thread with lambda (captures nothing)
    thread t2([](){
        cout << "[lambda] Hello from thread " << this_thread::get_id() << "\n";
    });

    // 3) Start thread with argument (by value)
    thread t3(print_number, 42);

    // 4) Detached thread (no join; let it run on its own)
    thread t4([](){
        cout << "[detached] Starting work on " << this_thread::get_id() << "\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "[detached] Done\n";
    });
    t4.detach();

    // Join the joined threads
    t1.join();
    t2.join();
    t3.join();

    // Give detached thread time to finish before main exits
    this_thread::sleep_for(chrono::milliseconds(150));

    cout << "All threads finished (joined + detached).\n";
    return 0;
}
