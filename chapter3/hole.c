#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char **argv)
{
    int fd;
    if ((fd = open("file.hole", O_CREAT| O_WRONLY| O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {
        err(EXIT_FAILURE, "Failed to creat file");
        return -1;
    }
    
    printf("%d\n", fd);

    if ((write(fd, buf1, 10)) == -1) {
        err(EXIT_FAILURE, "Failed to write buf1");
        return -1;
    }

    if ((lseek(fd, 16384, SEEK_SET)) == -1) {
        err(EXIT_FAILURE, "lseek failed");
        return -1;
    }

    if ((write(fd, buf2, 10)) == -1) {
        err(EXIT_FAILURE, "Failed to write buf2");
        return -1;
    }

    return 0;
}
