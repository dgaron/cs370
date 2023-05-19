#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "Pell.h"

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SHM_SIZE 32    

#include <errno.h>
#include <string.h>

int getPellNumber(int n) {
    if (n == 0) {
      return 0;
    }
    return round(( -pow((1 - sqrt(2.0)), n) + pow((1 + sqrt(2.0)), n) / 
           (2 * sqrt(2.0))));
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr,"%s: Improper number of args passed via execlp()\n", argv[0]);
        exit(1);
    }

    int numNumbers = atoi(argv[2]);

    printf("Pell[%d]: Number of terms in Pell series is %d\n", getpid(), numNumbers);
    printf("Pell[%d]: The first %d numbers of the Pell sequence are:\n", getpid(), numNumbers);

    int pellNum;
    for (int i = 0; i < numNumbers; ++i) {
        pellNum = getPellNumber(i);
        printf("%d, ", pellNum);
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
    sprintf(ptr,"%d", pellNum);

    exit(0);
}
