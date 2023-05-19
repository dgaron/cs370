#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "Pell.h"

int getPellNumber(int n) {
  if (n == 0) {
    return 0;
  }
  return round(( -pow((1 - sqrt(2.0)), n) + pow((1 + sqrt(2.0)), n) / 
         (2 * sqrt(2.0))));
}

int main(int argc, char *argv[]) {
  (void) argc;
  int numNumbers = atoi(argv[1]);

  printf("Pell[%d]: Number of terms in Pell series is %d\n", getpid(), numNumbers);
  printf("Pell[%d]: The first %d numbers of the Pell sequence are:\n", getpid(), numNumbers);

  int pellNum;
  for (int i = 0; i < numNumbers; ++i) {
    pellNum = getPellNumber(i);
    printf("%d, ", pellNum);
  }
  printf("\n");

  exit(pellNum);
}
