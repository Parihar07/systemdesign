#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <unistd.h> // getpid()

using namespace std;

int global_var_single = 42;
static volatile uint64_t blackhole_single = 0; // prevents over-optimization

uint64_t do_work_single(uint64_t n) {
    uint64_t s = 0;
    for (uint64_t i = 1; i <= n; ++i) s += i * i;
    blackhole_single = s;
    return s;
}

int main() {
    cout << "Single-thread basics" << "\n";
    cout << "PID: " << getpid() << "\n";
    cout << "Main thread id: " << this_thread::get_id() << "\n";

    int local_var = 7;
    int* heap_var = new int(99);

    cout << "Addresses (virtual):\n";
    cout << "  &local_var (stack): " << &local_var << "\n";
    cout << "  heap_var (heap):    " << heap_var   << "\n";
    cout << "  &global_var (data): " << &global_var_single << "\n";

    const uint64_t N = 3'000'000; // keep within 64-bit for sum of squares

    auto t0 = chrono::high_resolution_clock::now();
    auto result = do_work_single(N);
    auto t1 = chrono::high_resolution_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

    cout << "Work: sum_{i=1.." << N << "} i^2" << "\n";
    cout << "Result: " << result << "\n";
    cout << "Elapsed: " << us << " us\n";

    delete heap_var;
    return 0;
}
