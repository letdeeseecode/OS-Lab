#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(1);
    }

    const char *message = argv[1];

    // Open the FIFO for writing
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Write the message to the FIFO
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        exit(1);
    }

    close(fd);

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read acknowledgment from the FIFO
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("Received: %s\n", buffer);
    } else if (bytesRead == -1) {
        perror("read");
    }

    close(fd);

    return 0;
}
