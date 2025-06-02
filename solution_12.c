#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#define FILENAME "process_log.txt"

int main() {
    struct timeval start, end;

    // Record start time
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);

    } else if (pid == 0) {
        // Child process work
        printf("Child (PID: %d) running...\n", getpid());

        // Simulate workload with sleep
        sleep(2);  // sleep for 2 seconds

        printf("Child finished.\n");
        exit(0);
    } else {
        // Parent waits for child
        wait(NULL);

        // Record end time
        gettimeofday(&end, NULL);

        // Calculate elapsed time
        long seconds = end.tv_sec - start.tv_sec;
        long micros = end.tv_usec - start.tv_usec;
        //error handling
        if (micros < 0) {       
            seconds -= 1;
            micros += 1000000;
        }

        // Write to file
        FILE *file = fopen(FILENAME, "w");
        if (file == NULL) {
            perror("File open error");
            exit(1);
        }

        fprintf(file, "Submission Time: %ld.%06ld\n", (long)start.tv_sec, (long)start.tv_usec);
        fprintf(file, "Finish Time:     %ld.%06ld\n", (long)end.tv_sec, (long)end.tv_usec);
        fprintf(file, "Elapsed Time:    %ld.%06ld seconds\n", seconds, micros);
        fclose(file);

        printf("Timing written to '%s'.\n", FILENAME);
    }

    return 0;
}
