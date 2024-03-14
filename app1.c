#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

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

    strcpy(map, "Hello from App 1!");
    printf("App 1 wrote: %s\n", map);

    // Cleanup
    munmap(map, getpagesize());
    close(fd);

    return 0;
}

