// program2.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 0x1234 // Must match the writer

int main() {
    int shmid;
    int *shared_mem;

    // Access the existing shared memory
    shmid = shmget(SHM_KEY, sizeof(int), 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    shared_mem = (int *)shmat(shmid, NULL, 0);
    if (shared_mem == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read PID
    printf("Read PID %d from shared memory.\n", *shared_mem);

    // Detach
    if (shmdt(shared_mem) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("Shared memory segment removed successfully.\n");

    return 0;
}
