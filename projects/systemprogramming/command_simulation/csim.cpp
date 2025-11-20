/*
 * PROBLEM: Simulate Shell Pipeline Command `ls | wc -l`
 *
 * Implement a C++ program that replicates the behavior of the shell command
 * `ls | wc -l` (count number of files in current directory) using:
 * - Multiple processes (fork)
 * - Pipes for inter-process communication
 * - File descriptor redirection (dup2)
 *
 * Requirements:
 * 1. Create TWO child processes (one for ls, one for wc)
 * 2. Use a pipe to connect ls output to wc input
 * 3. First child executes `ls` command
 * 4. Second child executes `wc -l` command
 * 5. Use dup2() to redirect:
 *    - ls stdout → pipe write end
 *    - wc stdin → pipe read end
 * 6. Parent waits for both children to complete
 * 7. Properly close all pipe file descriptors in all processes
 *
 * Expected Output:
 *   [Similar to running: ls | wc -l]
 *        3
 *   (Shows count of files in current directory)
 *
 * Key Concepts:
 * - File descriptors: stdin(0), stdout(1), stderr(2)
 * - dup2(old_fd, new_fd): Redirects new_fd to point to old_fd
 * - Pipe creates unidirectional data flow: write end → read end
 * - execlp() replaces process image with new program
 * - Processes run in parallel but synchronized via pipe
 * - Pipe buffer (~64KB) provides flow control
 *
 * Learning Points:
 * - Understanding "everything is a file" in Unix
 * - File descriptor table manipulation
 * - Process creation and replacement
 * - Inter-process communication via pipes
 * - Shell pipeline implementation internals
 */

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

int main()
{
    cout << "Hello simulating shell command 'ls | wc -l'\n";
    cout << "Main program PID: " << getpid() << endl;
    pid_t p1, p2;

    // Create ONE pipe: ls → wc (you only need one pipe for unidirectional flow)
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        cout << "Pipe creation failed\n";
        return 1;
    }

    // Child 1: Execute 'ls' and send output to pipe
    p1 = fork();
    if (p1 == 0)
    {
        cout << "[Child 1 - ls] PID: " << getpid() << endl;

        // Redirect stdout to pipe write end
        dup2(pipefd[1], STDOUT_FILENO); // ls output goes to pipe

        // Close both pipe ends (dup2 already copied the fd)
        close(pipefd[0]);
        close(pipefd[1]);

        execlp("ls", "ls", nullptr);
        exit(1); // Only if exec fails
    }

    // Child 2: Execute 'wc -l' and read input from pipe
    p2 = fork();
    if (p2 == 0)
    { 
        cout << "[Child 2 - wc] PID: " << getpid() << endl;

        // Redirect stdin from pipe read end
        dup2(pipefd[0], STDIN_FILENO); // wc reads from pipe

        // Close both pipe ends
        close(pipefd[0]);
        close(pipefd[1]);

        execlp("wc", "wc", "-l", nullptr);
        exit(1); // Only if exec fails
    }

    // Parent: Close pipe ends and wait for both children
    close(pipefd[0]);
    close(pipefd[1]);

    cout << "[Parent] PID: " << getpid() << " - Waiting for children...\n";
    wait(NULL); // Wait for child 1
    wait(NULL); // Wait for child 2
    cout << "[Parent] Both children completed!\n";

    return 0;
}