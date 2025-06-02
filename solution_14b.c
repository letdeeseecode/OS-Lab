#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SEM_KEY_A 5678
#define SEM_KEY_B 5679
#define SHM_SIZE 1024

void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    int shmid, sem1, sem2;
    char *shm_ptr;

    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    shm_ptr = (char *)shmat(shmid, NULL, 0);

    sem1 = semget(SEM_KEY_A, 1, 0666);
    sem2 = semget(SEM_KEY_B, 1, 0666);

    for (int i = 0; i < 5; i++) {
        sem_wait(sem1);

        // Read data
        printf("Program 2: Read message %d: %s\n", i + 1, shm_ptr);

        sem_signal(sem2);
    }

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(sem1, 0, IPC_RMID);
    semctl(sem2, 0, IPC_RMID);

    printf("Program 2: Cleanup complete.\n");
    return 0;
}
