#include <iostream>
#include <unistd.h>     // fork, execlp, getpid, getppid
#include <sys/wait.h>   // waitpid

using namespace std;

int main() {
    cout << "Process creation basics\n";
    cout << "Parent PID: " << getpid() << "\n";

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        cout << "[child] PID: " << getpid() << ", PPID: " << getppid() << "\n";

        // Replace child image with a simple program (ls)
        // execlp only returns on failure
        execlp("ls", "ls", "-1", (char*)nullptr);
        perror("execlp failed");
        _exit(127); // exit child if exec fails
    } else {
        // Parent process
        int status = 0;
        pid_t w = waitpid(pid, &status, 0);
        if (w == -1) {
            perror("waitpid failed");
            return 1;
        }
        if (WIFEXITED(status)) {
            cout << "[parent] Child exited with code " << WEXITSTATUS(status) << "\n";
        } else if (WIFSIGNALED(status)) {
            cout << "[parent] Child killed by signal " << WTERMSIG(status) << "\n";
        } else {
            cout << "[parent] Child ended abnormally\n";
        }
    }

    return 0;
}
