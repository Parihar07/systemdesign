#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

void hello()
{
    cout << "hello form helelo function : " << getpid() << endl;
}

void longProcessing()
{
    for (size_t i = 0; i < 1000; i++)
    {
        cout << "child executing : " << i << "--" << "pid-" << getpid() << "  ParentId - " << getppid() << endl;
    }
}

int main()
{
    cout << "Hello process experiments .\n";
    cout << "Main thread, or parent : " << getpid() << endl;
    int k = 23;

    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        cout << "child creation failed\n";
        return 1;
    }
    else if (child_pid == 0)
    {
        cout << "Child created : pid of child " << getpid() << " Parent Id : " << getppid() << endl;
        //childProcess();
    }
    else
    {
        k = 45645;
        cout << "Parent stuff" << k << endl;
        longProcessing();
        hello();
    }

    return 0;
}