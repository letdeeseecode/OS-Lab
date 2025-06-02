#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_QUEUE_KEY 1234  // Unique key for message queue
#define MSG_SIZE 1024

// Message structure
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer message;

    // Create message queue and get its ID
    msgid = msgget(MSG_QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Print message queue ID in stderr
    fprintf(stderr, "Server: Message Queue ID: %d\n", msgid);

    // Receive message from client
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Server: Received message - %s\n", message.msg_text);

    // Send acknowledgment to client
    message.msg_type = 2;  // Message type 2 for acknowledgment
    strcpy(message.msg_text, "ACK: Message received by server.");
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Server: Sent acknowledgment to client.\n");

    // Remove the message queue (using msgctl)
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl removal failed");
        exit(1);
    }
    printf("Server: Message queue removed successfully.\n");

    return 0;
}
