#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    int ret, status;

    printf("PID: %d\n", getpid());

    printf("Forking new process...\n");
    if ((pid = fork()) == -1) {  // error
        perror("fork()");
    } else if (pid == 0) {  // child
        printf("  Child PID: %d\n", getpid());
        return 0;
    }

    ret = waitpid(pid, &status, 0);
    if (ret == -1) {
        perror("waitpid()");
        exit(1);
    }

    printf("\nCreate new PID namespaces...\n");
    ret = unshare(CLONE_NEWPID);
    if (ret == -1) {
        perror("unshare()");
        exit(1);
    }

    printf("PID: %d\n", getpid());

    printf("Forking new process...\n");
    if ((pid = fork()) == -1) {  // error
        perror("fork()");
    } else if (pid == 0) {  // child
        printf("  Child PID: %d\n", getpid());
        return 0;
    }

    ret = waitpid(pid, &status, 0);
    if (ret == -1) {
        perror("waitpid()");
        exit(1);
    }

    return 0;
}

