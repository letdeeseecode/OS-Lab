#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void signal_handler(int sig) {
    printf("Received signal: %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // Register signal handlers for various signals
    for (int i = 1; i < NSIG; i++) {
        if (sigaction(i, &sa, NULL) == -1) {
            // Some signals cannot be caught; ignore errors
            continue;
        }
    }

    printf("Signal Receiver Process ID: %d\n", getpid());
    printf("Waiting for signals...\n");

    // Infinite loop to keep the program running and waiting for signals
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}
