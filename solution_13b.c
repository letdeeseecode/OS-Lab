#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

#define SEM_KEY 1234
#define FILE_NAME "shared_file.txt"

void read_file() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[256];
    printf("Program 2 reading file contents:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
    printf("\n");
}

int main() {
    int semid;
    
    // Get the existing semaphore
    semid = semget(SEM_KEY, 1, 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }

    // Wait for signal from program1
    struct sembuf wait = {0, -1, 0};
    semop(semid, &wait, 1);

    read_file(); // Read the file

    printf("Program 2 finished reading.\n");

    // Remove the semaphore after use
    semctl(semid, 0, IPC_RMID);
    printf("Semaphore removed successfully.\n");

    return 0;
}
