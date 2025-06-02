#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

#define SHM_KEY 1234
#define SEM_KEY_A 5678
#define SEM_KEY_B 5679
#define SHM_SIZE 1024

void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0}; // Decrement semaphore (wait)
    semop(semid, &op, 1);
}

void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0}; // Increment semaphore
    semop(semid, &op, 1);
}

int main() {
    int shmid, sem1, sem2;
    char *shm_ptr;

    // Create shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    shm_ptr = (char *)shmat(shmid, NULL, 0);

    // Create semaphores
    sem1 = semget(SEM_KEY_A, 1, IPC_CREAT | 0666);
    sem2 = semget(SEM_KEY_B, 1, IPC_CREAT | 0666);

    // Initialize semaphores
    semctl(sem1, 0, SETVAL, 1); // A starts as 1
    semctl(sem2, 0, SETVAL, 0); // B starts as 0

    for (int i = 0; i < 5; i++) {
        sem_wait(sem2); // Wait for B

        // Write data
        sprintf(shm_ptr, "Message %d from prog1", i + 1);
        printf("Program 1: Wrote message %d\n", i + 1);

        sem_signal(sem1); // Signal A
    }

    shmdt(shm_ptr);
    return 0;
}
