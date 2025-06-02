#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE 256

int main() {
    // Create the FIFO with read/write permissions for all users
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    char buffer[BUFFER_SIZE];

    
        // Open the FIFO for reading
        int fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        

        // Read data from the FIFO
        ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("Received: %s\n", buffer);
        } else if (bytesRead == -1) {
            perror("read");
        }

        close(fd);

        // Send acknowledgment
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        }

        const char *ack = "ACKNOWLEDGEMENT";
        if (write(fd, ack, strlen(ack)) == -1) {
            perror("write");
        }

        close(fd);
    }

    // Remove the FIFO
    unlink(FIFO_NAME);

    return 0;
}
