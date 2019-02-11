#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void list_files(void) {
    int before_errno;
    DIR *dir;
    struct dirent *dirent;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir()");
        exit(1);
    }
    before_errno = errno;
    while ((dirent = readdir(dir)) != NULL)
        printf("  %s\n", dirent->d_name);
    if (errno != before_errno) {
        perror("readdir()");
        exit(1);
    }
}

int main(void) {
    int ret;
    char path[] = "/home/yamazaki/chroot_test";
    char buf[1024];

    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd()");
        exit(1);
    }
    printf("Before chroot(): %s\n", buf);
    list_files();

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
    list_files();

    printf("\nAttempt to escape from chrooted-/\n");

    // create foo directory and chroot to it
    ret = mkdir("foo", 0755);
    if (ret == -1) {
        perror("mkdir()");
        exit(1);
    }
    ret = chroot("foo");
    if (ret == -1) {
        perror("chroot()");
        exit(1);
    }

    // after chroot to foo directory, attempt to escape upper directory
    // than original chrooted directory (chroot_test directory)
    ret = chdir("..");
    if (ret == -1) {
        perror("chdir()");
        exit(1);
    }

    // this will be always failed because cwd is outside of chrooted-/
    // so only print error and ignore
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd()");
        // exit(1);
    }
    printf("After attempting to escape from chroot() %s\n", buf);
    list_files();
}

