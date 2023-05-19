#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Composite.h"

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
  (void) argc;
  int numNumbers = atoi(argv[1]);

  printf("Composite[%d]: First %d composite numbers are:\n", getpid(), numNumbers);

  int n = 1;
  int next;
  for (int i = 0; i < numNumbers; ++i) {
    next = getNextComposite(n);
    printf("%d, ", next);
    n = next;
  }
  printf("\n");

  exit(next);
}
