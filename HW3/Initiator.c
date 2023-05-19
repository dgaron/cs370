#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define exe0 "Pell"
#define exe1 "Composite"
#define exe2 "Total"

#define BUFFER_SIZE 10
#define READ_END 0
#define WRITE_END 1

#define SHM_SIZE 32

/*  Forks a child process to run the selected executable
 *  passes arg1 and arg2 as command line arguments
 */
int forkChild(const char *exeName, const char *arg1, const char *arg2) {
    // Create filepath string
    char exePath[32] = "./";
    strcat(exePath, exeName);

    // Flush output buffer before fork()
    fflush(stdout);

    pid_t cid = fork();

    if (cid < 0) {  // Fork failed
        return -1;
    } else if (cid == 0) {  // Child process
        // Execute desired program
        execlp(exePath, exeName, arg1, arg2, NULL);
    }
    return 0;
}

/*  main function
 *
 *  Creates a pipe for communication with child process
 *  
 *  First child parses a txt file for integers returning the sum via the pipe
 *
 *  Three subsequent child processes are created to process the sum
 *  The result of each process is printed to shared memory
 *
 *  Shared memory is closed and results are printed to standard output
 */
int main(int argc, char *argv[]) {

    // Print usage message if user enters improper number of arguments
    if (argc != 2) {
        fprintf(stderr,"Usage: %s <input file name>\n", argv[0]);
        return -1;
    }

    // Array containing the executable file names
    const char *childExeFiles[3] = {exe0, exe1, exe2};

    // Char arrays for pipe communication
    char read_msg[BUFFER_SIZE];

    // int array for pipe creation
    int fd[2];

    // Create pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "%s: Pipe failed", argv[0]);
        return -1;
    }

    // char array to store file descriptor
    char fileDes[10];
    sprintf(fileDes, "%d", fd[WRITE_END]);

    // Fork child to execute Reader
    if (forkChild("Reader", argv[1], fileDes) == -1) {
        fprintf(stderr, "%s: fork() failed for %s\n", argv[0], "Reader");
        return -1;
    }

    // Wait for Reader to complete
    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        if(WEXITSTATUS(status) == 1) {
          fprintf(stderr, "%s: Reader failed to read from file\n", argv[0]);
        return -1;
        }
    }

    // Close the write end        
    close(fd[WRITE_END]);
    // Read from the pipe
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    // Close the read end
    close(fd[READ_END]);

    // Only parent process reaches this point

    printf("Initiator[%d]: Contents read from the read-end pipe: %s\n", getpid(), read_msg);

    // Array containing the shared memory names
    const char *shmNames[3] = {"SHM_"exe0, "SHM_"exe1, "SHM_"exe2}; 
    int shm_fd;  // Shared memory file descriptor
    char *ptr[3];  // Shared memory pointers

    // Create child process with shared memory region for each executable
    for (int i = 0; i < 3; ++i) {

        // Create shared memory segment
        shm_fd = shm_open(shmNames[i], O_CREAT | O_RDWR, 0666);
       
        ftruncate(shm_fd, SHM_SIZE);
        
        ptr[i] = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr[i] == MAP_FAILED) {
		fprintf(stderr, "%s: Map failed\n", argv[0]);
		return -1;
	}

        printf("Initiator[%d]: Created shared memory \"%s\" with FD: %d\n", getpid(), shmNames[i], shm_fd);

        // Fork child process to execute selected program
        if (forkChild(childExeFiles[i], shmNames[i], read_msg) == -1) {
            fprintf(stderr, "%s: fork() failed for %s\n", argv[0], childExeFiles[i]);
            return -1;
        }
    }

    // Only parent process reaches this point
    // Wait for all three child processes to complete
    wait(NULL);
    wait(NULL);
    wait(NULL);

    // Print the value from shared memory and unlink the shared memory segment
    for (int i = 0; i < 3; ++i) {
        printf("Initiator[%d]: %s last number: %d\n", getpid(), childExeFiles[i], atoi(ptr[i]));
        if (shm_unlink(shmNames[i]) == -1) {
            printf("Error removing %s\n", "SHM_Pell");
            return -1;
        }
    }

    return 0;
}
