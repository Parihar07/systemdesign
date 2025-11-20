#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstring>    // for strlen()
#include <sys/wait.h> // for wait()
using namespace std;

int main()
{
    cout << "Hello understanding IPC basics..\n";

    // creating pipe
    int pipefd[2]; // 0 is for read and 1 is for write
    if (pipe(pipefd) == -1)
    {
        cout << "error creating pipe\n";
        return 1;
    }

    // lets create another process
    pid_t anotherprocess = fork();
    if (anotherprocess < 0)
    {
        cout << "another process creation failed\n";
        return 1;
    }

    // as we know as of now we have two processes
    if (anotherprocess == 0)
    {
        // Child process - close unused read end
        close(pipefd[0]);

        cout << "Child process with pid : " << getpid() << endl;
        const char *msg = "Hello from child process\n";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
    }
    else
    {
        // Parent process - close unused write end
        close(pipefd[1]);

        cout << "Parent process with pid: " << getpid() << endl;
        char buff[1000];
        read(pipefd[0], buff, 1000);
        cout << "Data read from child process: " << buff;
        close(pipefd[0]);

        // Wait for child to prevent zombie
        wait(nullptr);
    }

    return 0;
}