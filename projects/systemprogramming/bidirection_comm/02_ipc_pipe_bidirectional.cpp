/*
 * PROBLEM: Bidirectional Parent-Child Communication using Pipes
 *
 * Implement a continuous bidirectional chat system between parent and child processes.
 *
 * Requirements:
 * 1. Use TWO pipes for bidirectional communication (parent→child, child→parent)
 * 2. Parent should prompt user for input and send messages to child
 * 3. Child should automatically respond to received messages
 * 4. Support continuous communication in a loop
 * 5. Allow graceful shutdown when user types "exit"
 * 6. Properly close all unused pipe ends to prevent deadlocks
 * 7. Prevent zombie processes using wait()
 *
 * Expected Output:
 *   [Parent] Chat started. Type 'exit' to quit.
 *   [Parent] Enter message: hello
 *   [Child] Received: hello
 *   [Parent] Child replied: Child received: hello
 *   [Parent] Enter message: exit
 *   [Parent] Exiting...
 *   [Child] Parent disconnected. Exiting...
 *
 * Key Concepts:
 * - Protocol design: Parent writes first, child reads first (avoid deadlock)
 * - Blocking I/O: read() blocks until data available
 * - Pipe synchronization between independent processes
 * - Proper resource cleanup
 */

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

    // Pipe 1: Parent → Child
    int pipe_p2c[2]; // Parent writes to [1], Child reads from [0]
    if (pipe(pipe_p2c) == -1)
    {
        cout << "error creating parent-to-child pipe\n";
        return 1;
    }

    // Pipe 2: Child → Parent
    int pipe_c2p[2]; // Child writes to [1], Parent reads from [0]
    if (pipe(pipe_c2p) == -1)
    {
        cout << "error creating child-to-parent pipe\n";
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
        // Child process - close unused pipe ends
        close(pipe_p2c[1]); // Won't write to parent→child pipe
        close(pipe_c2p[1]); // Won't read from child→parent pipe

        cout << "[Child " << getpid() << "] Ready to receive messages...\n";

        while (true)
        {
            // Reading data from parent
            char cbuff[1000];
            int n = read(pipe_p2c[0], cbuff, 1000);

            if (n <= 0 || strcmp(cbuff, "exit") == 0)
            {
                cout << "[Child] Parent disconnected. Exiting...\n";
                break;
            }

            cout << "[Child] Received: " << cbuff << endl;

            // Auto-response from child
            string response = "Child received: " + string(cbuff);
            write(pipe_c2p[1], response.c_str(), response.length() + 1);
        }

        // Close remaining pipe ends
        close(pipe_p2c[0]);
        close(pipe_c2p[1]);
    }
    else
    {
        // Parent process - close unused pipe ends
        close(pipe_p2c[0]); // Won't read from parent→child pipe
        close(pipe_c2p[1]); // Won't write to child→parent pipe

        cout << "[Parent " << getpid() << "] Chat started. Type 'exit' to quit.\n";

        while (true)
        {
            // Parent sends message first
            cout << "[Parent] Enter message: ";
            string pInput = "";
            getline(cin, pInput);

            write(pipe_p2c[1], pInput.c_str(), pInput.length() + 1);

            if (pInput == "exit")
            {
                cout << "[Parent] Exiting...\n";
                break;
            }

            // Then read child's response
            char pbuff[1000];
            read(pipe_c2p[0], pbuff, 1000);
            cout << "[Parent] Child replied: " << pbuff << endl
                 << endl;
        }

        // Close remaining pipe ends
        close(pipe_p2c[1]);
        close(pipe_c2p[0]);

        // Wait for child to prevent zombie
        wait(nullptr);
    }

    return 0;
}