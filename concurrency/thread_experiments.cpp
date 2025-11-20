#include<iostream>
#include<vector>
#include<string>
#include<thread>
using namespace std;

void hello() {
    cout << "hello from hello function\n";
    for (size_t i = 0; i < 100; i++)
    {
        cout << "loop : " << i << endl;
    }
    return;
}

int main()
{
    cout<<"Hello thread experiments..\n";
    thread t1(hello);
    // t1.join();
    return 0;
}