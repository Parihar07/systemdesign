#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
int counter = 0;

auto my_chcek()
{
    if (counter < 3)
    {
        return true;
    }
    return false;
}

// void pooled_worker(int tid) /// one of the version
// {
//     {
//         unique_lock<mutex> cs_lock(mtx);
//         cv.wait(cs_lock, my_chcek);
//         counter++;
//         cout << "Thread " << tid << " entered. Active: " << counter << endl;
//     }
//     for (int i = 0; i < 10; i++)
//     {
//         cout << "working in : " << tid << "\n";
//     }
//     {
//         unique_lock<mutex> cs_lock(mtx);
//         counter--;
//         cout << "Thread " << tid << " leaving. Active: " << counter << endl;
//         cv.notify_all();
//     }
// }

void pooled_worker(int tid) /// one of the version
{

    unique_lock<mutex> cs_lock(mtx);
    cv.wait(cs_lock, my_chcek);
    counter++;
    cout << "Thread " << tid << " entered. Active: " << counter << endl;
    cs_lock.unlock();

    this_thread::sleep_for(chrono::milliseconds(1000));
    for (int i = 0; i < 10; i++)
    {
        cout << "working in : " << tid << "\n";
    }

    unique_lock<mutex> cs_lock2(mtx);
    counter--;
    cout << "Thread " << tid << " leaving. Active: " << counter << endl;
    cv.notify_all();
    cs_lock2.unlock();
}

int main()
{
    cout << "Hello implemention of connection pool or implementing semaphore..\n";

    vector<thread> vthreads;
    for (int i = 0; i < 10; i++)
    {
        vthreads.emplace_back(pooled_worker, i);
    }

    for (auto &t : vthreads)
    {
        t.join();
    }
}