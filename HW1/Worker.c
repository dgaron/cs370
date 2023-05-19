#include <stdio.h>
#include <stdlib.h>

#include "Worker.h"

#define ITERATIONS_LOWER 50
#define ITERATIONS_UPPER 100
#define ARRAY_LOWER 100
#define ARRAY_UPPER 150
#define ELEMENT_LOWER 1
#define ELEMENT_UPPER 100
#define DIVISOR_LOWER 5
#define DIVISOR_UPPER 15

/* It is responsible for implementing the following:
 * 1. Dynamically allocate and de-allocate a random sized array for each iteration.
 * 2. Populate elements in the array with random integers.
 * 3. For each iteration, generate a random integer to be used as a divisor.
 * 4. For each element in the array, check if the element is divisible, and if so count it.
 * 5. Calculate the ratio of elements divisible by divisor to elements not divisible by the divisor.
 * ---- Number of Divisible Elements /Number of Non-Divisble Elements ----
 * 6. At the end print the iteration number with maximum number of divisible elements.
 * 7. Return the average value of the ratio divisible/not_divisible for all iterations to Initiator
 * Hint: you are computing the total number of divisible items over the total
 * number of iterations
 */

/*
 * This function returns a random integer within the specified range.
 *   Lower bound is inclusive
 *   Upper bound is exclusive
 */
int random_in_range(int lower_bound, int upper_bound) {
    return ((rand() % (upper_bound - lower_bound)) + lower_bound);
}

/*
 * This function will count the number of elements in the specified array
 * that are divisible by the supplied dividend
 */
int get_divisibility_count(int *array, int arraySize, int randomDividend) {
    int numDivisions = 0;
    for (int i = 0; i < arraySize; ++i) {
        if ((array[i] % randomDividend) == 0) {
            ++numDivisions;
        } 
    }
    return numDivisions;
}

/*
 * This function will populate a provided array with random integers.
 */
void populate_array(int *numbers, int numbersLength) {
    
    for (int j = 0; j < numbersLength; ++j) {
        numbers[j] = random_in_range(ELEMENT_LOWER, ELEMENT_UPPER);
    }
}

/*
 * This function will populate an array of random size with random elements.
 * It will then test the divisibility of those array elements by a random dividend.
 * It returns the average divisibility ratio.
 */
double get_running_ratio() {

    int maxDivisibleElements = 0;
    int maxCountIteration = 0;

    double divRatioSum = 0.0;

    // Use RNG to compute the number of allocations & deallocations
    int numIterations = random_in_range(ITERATIONS_LOWER, ITERATIONS_UPPER);

    // Declare and populate a specified number of arrays
    for (int i = 0; i < numIterations; ++i) {
        int arraySize = random_in_range(ARRAY_LOWER, ARRAY_UPPER);

        // Allocate space for the array on the heap
        int* numbers = calloc(arraySize, sizeof(int));
        
        // Populate array
        populate_array(numbers, arraySize);

        // Obtain random dividend and determine divisibility
        int randomDividend = random_in_range(DIVISOR_LOWER, DIVISOR_UPPER);
        int numDivisions = get_divisibility_count(numbers, arraySize, randomDividend);
        
        // Keep a running tally of the divisibility ratio
        divRatioSum += ((double) numDivisions) / (arraySize - numDivisions);

	// Track the maximum number of divisions possible among the arrays
        if (numDivisions > maxDivisibleElements) {
            maxDivisibleElements = numDivisions;
            maxCountIteration = i + 1;
        }

        // Deallocate the memory for the array
        free(numbers);
    }

    printf("[Worker]: Number of iterations is: %d\n", numIterations);
    printf("[Worker]: Iteration with maximum fully divisible elements is %d\n", maxCountIteration);
    return (divRatioSum / numIterations);
}



