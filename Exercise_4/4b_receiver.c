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
    int msg_id;
    struct msgbuf msg;
    // Access the message queue
    msg_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_id < 0)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    // Receive a message of any type
    if (msgrcv(msg_id, &msg, sizeof(msg.mtext), 0, 0) < 0)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    printf("Received: %s\n", msg.mtext);
    // Optionally remove the message queue
    if (msgctl(msg_id, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    return 0;
}