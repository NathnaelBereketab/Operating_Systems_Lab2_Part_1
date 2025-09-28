#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork(); // create a new process

    if (pid < 0) {
        // fork failed
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // child
        printf("Child process: My PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else {
        // parent
        printf("Parent process: My PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}

