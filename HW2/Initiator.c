#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
  (void) argc;

  // Integer to store the return value of the child process
  int status;

  // Array containing the executable file names
  const char *childExeFiles[3] = {"Pell", "Composite", "Total"};

  // Integer array to contain the return values of the child processes
  int returnValues[3];

  // Open and read numbers from text file specified by argv[1]
  FILE *file = fopen(argv[1], "r");

  // Error handling for invalid file name
  if (file == NULL) {
    fprintf(stderr, "%s: Can't open file: %s\n", argv[0], argv[1]);
    return(1);
  }

  // Char array to store the contents of each line read
  char lineBuffer[255];

  // Execute child processes for each line read
  while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL) {

    // Create child process for each executable
    for (int i = 0; i < 3; ++i) {

      // Flush output buffer before fork
      fflush(stdout);

      // Create a duplicate process
      pid_t cid = fork();

      if (cid < 0) {  // Fork failed
        fprintf(stderr, "%s: Fork failed\n", argv[0]);
      } else if (cid == 0) {  // Child process
        // Create filepath string
        char fileWithPath[64] = "./";
        strcat(fileWithPath, childExeFiles[i]);

        // Execute desired program
        execlp(fileWithPath, childExeFiles[i], lineBuffer, NULL);
      } else {  // Parent Process
        printf("Initiator[%d]: Forked process with ID %d\n", getpid(), cid);
        printf("Initiator[%d]: Waiting for process [%d]\n", getpid(), cid);
        wait(&status);
        // Obtain exit status from child
        if (WIFEXITED(status)) {
          returnValues[i] = WEXITSTATUS(status);
          printf("Initiator: Child process %d returned %d\n", cid, WEXITSTATUS(status));
        } else {
          fprintf(stderr, "%s: Child process [%d] terminated abnormally\n", argv[0], cid);
        }
      }
    }
    printf("Pell: %d\n", returnValues[0]);
    printf("Composite: %d\n", returnValues[1]);
    printf("Total Count: %d\n", returnValues[2]);

  }
  
  // Error handling for file read failure
  if (ferror(file)) {
    fprintf(stderr, "%s: File read error", argv[0]);
    return 1;
  }

  fclose(file);
  return 0;
}
