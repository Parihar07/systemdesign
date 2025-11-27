#include <iostream>
#include <vector>
#include <string>
#include <thread>
using namespace std;

 atomic<int> serverCounter;

void write_worker()
{
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "writing : " << this_thread::get_id() << "\n";
    for (size_t i = 0; i < 10000; i++)
    {
        serverCounter++;
    }
}

int main()
{
    cout << "Hello. building traffic counter.\n";

    // creating mutiple threads here which will update server variable or counter

    thread t1(write_worker);
    thread t2(write_worker);
    thread t3(write_worker);
    thread t4(write_worker);
    thread t5(write_worker);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    cout << "\nAll threads finished." << endl;
    cout << "Expected server value: 50000" << endl;
    cout << "Actual server value  : " << serverCounter << endl;

    return 0;
}