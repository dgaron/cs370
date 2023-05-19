#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Total.h"

int getSum(int n) {
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += i;
  }
  return sum;
}

int main(int argc, char *argv[]) {
  (void) argc;
  int numNumbers = atoi(argv[1]);

  int sum = getSum(numNumbers);
  printf("Total [%d]: Sum = %d\n", getpid(), sum); 

  exit(sum);
}
