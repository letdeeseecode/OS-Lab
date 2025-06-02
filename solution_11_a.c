// program1.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 0x1234 // Shared memory key

int main() {
    int shmid;
    int *shared_mem;

    // Create shared memory segment of size int
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
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

    // Write PID
    *shared_mem = getpid();
    printf("Wrote PID %d to shared memory.\n", *shared_mem);

    // Detach
    if (shmdt(shared_mem) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
