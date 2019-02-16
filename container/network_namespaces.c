#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int ret;

    printf("Initial network namespace:\n");
    system("ip a");

    printf("\nEnter new network namespace:\n");
    ret = unshare(CLONE_NEWNET);
    if (ret == -1) {
        perror("unshare()");
        exit(1);
    }
    system("ip a");

    return 0;
}

