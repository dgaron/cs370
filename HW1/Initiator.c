#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"


/* It is responsible for:
 * 1. Setting the seed, whose value is passed as an argument, using srand().
 * 2. Invoking functions in the Worker.
 */

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        printf("This program requires one argument: <int>\n");
        exit(1);
    }

    int seed = atoi(argv[1]);

    if (seed < 0) {
        printf("Please enter a positive integer\n");
        exit(1);
    }

    srand(seed);
    printf("[Initiator]: With seed: %d\n", seed);

    double running_ratio = get_running_ratio();

    printf("[Initiator]: Running ratio: %f\n", running_ratio);

    return 0;
}



