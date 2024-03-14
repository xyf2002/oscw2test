#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("/dev/shmem", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    char *map = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }

    // Instead of writing to the memory, we'll just read from it
    printf("App 2 read: %s\n", map);

    // Optionally, you could write something else here
    // to test if the memory is indeed shared
    strcpy(map, "Hello from App 2!");

    // Cleanup
    munmap(map, getpagesize());
    close(fd);

    return 0;
}

