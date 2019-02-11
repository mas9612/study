#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int ret;
    char path[] = "/home/yamazaki/chroot_test";
    char buf[1024];

    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd()");
        exit(1);
    }
    printf("Before chroot(): %s\n", buf);

    // if this chdir() is omitted, last getcwd() will be failed because
    // chroot() doesn't change current working directory.
    // so after chroot(), cwd is outside of chrooted-/ and getcwd()
    // will fail.
    ret = chdir(path);
    if (ret == -1) {
        perror("chdir()");
        exit(1);
    }
    ret = chroot(path);
    if (ret == -1) {
        perror("chroot()");
        exit(1);
    }

    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd()");
        exit(1);
    }
    printf("After chroot() %s\n", buf);
}
