#include <stdio.h>      //basic input/output like printf(), [print error]perror()
#include <stdlib.h>     //exit()
#include <unistd.h>     //fork(), getpid(), getppid()
#include <sys/wait.h>   //wait()

int main() {
    pid_t child_pid, grandchild_pid;
    int child_count = 0;
    int grandchild_count = 0;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (child_pid == 0) {
        printf("Child Process:\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());

        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (grandchild_pid == 0) {
            printf("Grandchild Process:\n");
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
            printf("Some output\n"); 
            exit(0);
        } else {
            wait(NULL);
            exit(0); 
        }
    } else {
        
        child_count++;
        printf("Parent Process:\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
        printf("Child PID: %d\n", child_pid);
        
        wait(NULL);

        grandchild_count++;

        printf("Total number of child processes created: %d\n", child_count);
        printf("Total number of grandchild processes created: %d\n", grandchild_count);
    }

    return 0;
}
