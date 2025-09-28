#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t child1, child2;

    // first fork
    child1 = fork();

    if (child1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (child1 == 0) {
        // child 1
        srandom(time(NULL) ^ (getpid()<<16));
        int loops = random() % 30 + 1;
        for (int i = 0; i < loops; i++) {
            printf("Child Pid: %d is going to sleep!\n", getpid());
            sleep(random() % 10 + 1);
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0);
    } else {
        // parent forks second child
        child2 = fork();

        if (child2 < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (child2 == 0) {
            // child 2
            srandom(time(NULL) ^ (getpid()<<16));
            int loops = random() % 30 + 1;
            for (int i = 0; i < loops; i++) {
                printf("Child Pid: %d is going to sleep!\n", getpid());
                sleep(random() % 10 + 1);
                printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
            }
            exit(0);
        } else {
            // parent waits for both children
            int status;
            pid_t pid;
            for (int i = 0; i < 2; i++) {
                pid = wait(&status);
                printf("Child Pid: %d has completed\n", pid);
            }
        }
    }
    return 0;
}

