#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    // Open the file in read-write mode to allow exclusive locking.
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Failed to open file");
        exit(1);
    }

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;    // Requesting an exclusive lock
    lock.l_whence = SEEK_SET; // From the beginning of the file
    lock.l_start = 0;         // Starting offset
    lock.l_len = 0;           // Lock the whole file

    // Check if the file is already locked
    if (fcntl(fd, F_GETLK, &lock) == -1) {
        perror("fcntl");
        close(fd);
        exit(1);
    }

    if (lock.l_type != F_UNLCK) {
        // File is locked by another process
        printf("File is locked by another process (PID: %d).\n", lock.l_pid);
        close(fd);
        exit(1);
    }

    // File is not locked; attempt to acquire the lock
    lock.l_type = F_WRLCK; // Set exclusive lock
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to acquire lock");
        close(fd);
        exit(1);
    }

    printf("Lock acquired. Reading file...\n");
    sleep(5);

    // Read and display the file contents
    char buffer[256];
    ssize_t bytesRead;
    // Reset file offset to beginning before reading
    lseek(fd, 0, SEEK_SET);
    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }
    if (bytesRead == -1) {
        perror("Failed to read file");
    }

    printf("\nReleasing lock...\n");
    // Release the lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release lock");
        close(fd);
        exit(1);
    }
    printf("Lock released.\n");

    close(fd);
    return 0;
}
