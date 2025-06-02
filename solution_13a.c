#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <fcntl.h>
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
    printf("Program 1 reading file contents:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
    printf("\n");
}

int main() {
    int semid;
    
    // Create a semaphore (or get existing one)
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }

    // Set initial value of semaphore to 0 (first execution)
    semctl(semid, 0, SETVAL, 0);

    read_file(); // Read the file

    // Signal program2 by incrementing the semaphore
    struct sembuf signal = {0, 1, 0};
    semop(semid, &signal, 1);
    
    printf("Program 1 finished reading and signaled Program 2.\n");

    return 0;
}
