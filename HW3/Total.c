#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Total.h"

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SHM_SIZE 32    

int getSum(int n) {
    return (n*(n + 1)) / 2;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr,"%s: Improper number of args passed via execlp()\n", argv[0]);
        exit(1);
    }

    int numNumbers = atoi(argv[2]);

    int sum = getSum(numNumbers);
    printf("Total[%d]: Sum = %d\n", getpid(), sum); 

    int shm_fd;
    char *ptr;

    // Open the shared memory segment
    shm_fd = shm_open(argv[1], O_RDWR, 0666);
    if (shm_fd == -1) {
        fprintf(stderr, "%s: Shared memory failed\n", argv[0]);
        exit(1);
    }

    // Map the shared memory segment in the address space of the process
    ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
    fprintf(stderr, "%s: Map failed\n", argv[0]);
        exit(1);
    }

    // Write to shared memory
    sprintf(ptr,"%d", sum);

    exit(0);
}
