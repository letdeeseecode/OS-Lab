#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_QUEUE_KEY 1234  // Same key as server
#define MSG_SIZE 1024

// Message structure
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer message;

    // Get the message queue ID
    msgid = msgget(MSG_QUEUE_KEY, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Print message queue ID in stderr
    fprintf(stderr, "Client: Message Queue ID: %d\n", msgid);

    // Take user input
    printf("Client: Enter message to send: ");
    fgets(message.msg_text, MSG_SIZE, stdin);
    message.msg_text[strcspn(message.msg_text, "\n")] = '\0';  // Remove newline

    // Send message to server
    message.msg_type = 1;  // Message type 1 for client message
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Client: Message sent to server.\n");

    // Receive acknowledgment from server
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Client: Received acknowledgment - %s\n", message.msg_text);

    return 0;
}
