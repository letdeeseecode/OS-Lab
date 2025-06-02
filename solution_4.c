#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Signal handler function for SIGINT
void handle_sigint(int sig)
{
    pid_t pid;
    pid = fork(); // Fork a new process
    if (pid < 0)
    {
        perror("Fork failed"); // Fork failed
        exit(1);
    }
    else if (pid == 0)
    {
        // In child process
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        exit(0);
    }
    else
    {
        // In parent process
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        // Wait for child process to finish
        wait(NULL);
    }
}
int main()
{
    // Set up the SIGINT signal handler
    if (signal(SIGINT, handle_sigint) == SIG_ERR)
    {
        perror("Error setting up signal handler");
        exit(1);
    }
    // Inform the user
    printf("Press Ctrl+C to trigger the SIGINT signal handler...\n");
    // Infinite loop to keep the program running
    while (1)
    {
        pause(); // Wait for signals
    }
    return 0;
}
