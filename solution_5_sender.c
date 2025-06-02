#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int sig;

    // Prompt user for Process ID and Signal Number
    printf("Enter Process ID to send signal to: ");
    scanf("%d", &pid);
    printf("Enter Signal Number to send: ");
    scanf("%d", &sig);

    // Send the specified signal to the specified process
    if (kill(pid, sig) == -1) {
        perror("Failed to send signal");
        exit(1);
    }

    printf("Signal %d sent to process %d successfully.\n", sig, pid);

    return 0;
}
