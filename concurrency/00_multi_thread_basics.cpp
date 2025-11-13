
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <unistd.h>

using namespace std;

static volatile uint64_t blackhole_mt = 0; // prevents over-optimization

uint64_t do_work_range(uint64_t a, uint64_t b) {
    uint64_t s = 0;
    for (uint64_t i = a; i <= b; ++i) s += i * i;
    blackhole_mt = s;
    return s;
}

// Simple named worker: compute partial sum and add to total.
void worker(uint64_t start, uint64_t end, atomic<uint64_t>& total) {
    uint64_t part = do_work_range(start, end);
    total.fetch_add(part); // default (seq_cst) for clarity
}

int main() {
    cout << "Multi-thread basics" << "\n";
    cout << "PID: " << getpid() << "\n";
    cout << "Main thread id: " << this_thread::get_id() << "\n";

    const uint64_t N = 3'000'000; // sum of squares up to N
    const unsigned T = max(1u, thread::hardware_concurrency()); // logical cores

    atomic<uint64_t> total{0};
    vector<thread> threads;
    threads.reserve(T);

    // Split [1..N] into T chunks; one chunk per thread.
    uint64_t chunk = N / T;
    auto t0 = chrono::high_resolution_clock::now();

    for (unsigned ti = 0; ti < T; ++ti) {
        uint64_t start = ti * chunk + 1;
        uint64_t end = (ti == T - 1) ? N : (start + chunk - 1);
        threads.emplace_back(worker, start, end, ref(total));
    }

    // Wait for all threads to finish and accumulate into total.
    for (auto& th : threads) th.join();

    auto t1 = chrono::high_resolution_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

    cout << "Threads used: " << T << "\n";
    cout << "Work: sum_{i=1.." << N << "} i^2" << "\n";
    cout << "Total result: " << total.load() << "\n";
    cout << "Elapsed: " << us << " us\n";
    return 0;
}
