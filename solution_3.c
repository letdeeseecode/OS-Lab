#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        char *args[] = {"/filepath", "arg1", "arg2", NULL};  //declaring the execv()
        execv(args[0], args);   //using it
        perror("execv failed");     //error handling    
        exit(1);
    } else {
        // Parent process
        int status;
        wait(&status); //waits for the child to finish and stores its status info

        if (WIFEXITED(status)) {    //checks if child terminated normally or abnormally
            int exit_status = WEXITSTATUS(status);  //extracts the status info using the macro WEXITSTATUS 
                                                        //and store it in the variable exit_status
            printf("Child exited with status: %d\n", exit_status);  //and print it
        } else {
            printf("Child did not exit normally.\n");   //if terminated abnormally, then print it
        }
    }

    return 0;
}
