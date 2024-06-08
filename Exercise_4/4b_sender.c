#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msgbuf
{
    long mtype;      // message type must be > 0
    char mtext[200]; // message data
};
int main()
{
    key_t key = 1234; // predefined key
    int msgid;
    struct msgbuf msg;
    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    // Prepare a message to send
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello, this message is from sender");
    // Send the message
    if (msgsnd(msgid, &msg, strlen(msg.mtext), 0) < 0)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Sent: %s\n", msg.mtext);
    
    return 0;
}