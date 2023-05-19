#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Reader.h"

#define BUFFER_SIZE 10

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr,"%s: Improper number of args passed to execlp()\n", argv[0]);
        exit(1);
    }   
 
    // Open and read numbers from text file specified by argv[1]
    FILE *file = fopen(argv[1], "r");

    // Error handling for invalid file name
    if (file == NULL) {
      fprintf(stderr, "%s: Can't open file: %s\n", argv[0], argv[1]);
      exit(1);
    }

    // Int to store file contents
    int fileContents = 0;

    // Char array to store the contents of each line read
    char lineBuffer[255];

    // Execute child processes for each line read
    while (fgets(lineBuffer, sizeof(lineBuffer), file)) {
        fileContents += atoi(lineBuffer);
    }

    // Error handling for file read failure
    if (ferror(file)) {
      fprintf(stderr, "%s: File read error", argv[0]);
      exit(1);
    }

    fclose(file);

    // Convert pipe file descriptor to integer
    int fd = atoi(argv[2]);

    // char array to store file contents int result
    char write_msg[BUFFER_SIZE];
    // Store fileContents int as string in write_msg
    sprintf(write_msg, "%d", fileContents);

    // Write to the pipe
    write(fd, write_msg, strlen(write_msg) + 1);
    // Close write end
    close(fd);

    
    exit(0);    
}
