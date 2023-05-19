#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Composite.h"

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SHM_SIZE 32    

int getNextComposite(int n) {
    ++n;
    for (int i = 2; i <= (n / 2); ++i) {
        if ((n % i) == 0) {
            return n;
        }
    }
    return getNextComposite(n);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr,"%s: Improper number of args passed via execlp()\n", argv[0]);
        exit(1);
    }

    int numNumbers = atoi(argv[2]);

    printf("Composite[%d]: First %d composite numbers are:\n", getpid(), numNumbers);

    int n = 1;
    int next;
    for (int i = 0; i < numNumbers; ++i) {
        next = getNextComposite(n);
        printf("%d, ", next);
        n = next;
    }
    printf("\n");

    int shm_fd;
    char *ptr;

    // Open the shared memory segment
    shm_fd = shm_open(argv[1], O_RDWR, 0666);
    if (shm_fd == -1) {
        fprintf(stderr, "%s: shared memory failed\n", argv[0]);
        exit(1);
    }

    // Map the shared memory segment in the address space of the process
    ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
    fprintf(stderr, "%s: Map failed\n", argv[0]);
        exit(1);
    }   

    // Write to shared memory
    sprintf(ptr,"%d", next);

    exit(0);
}
