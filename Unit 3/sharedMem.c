#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
    key_t key = 1234; // Identifier for the shared memory segment
    int shmid;
    char *data;
    // Create the shared memory segment
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }
    // Attach the shared memory segment
    data = shmat(shmid, NULL, 0);
    if (data == (char *)(-1))
    {
        perror("shmat");
        exit(1);
    }
    // Write to the shared memory
    printf("Writing to shared memory: \"Hello, World!\"\n");
    strncpy(data, "Hello, World!", 1024);
    // Detach the shared memory
    if (shmdt(data) < 0)
    {
        perror("shmdt");
        exit(1);
    }
    // Reattach the shared memory to read from it
    data = shmat(shmid, NULL, 0);
    if (data == (char *)(-1))
    {
        perror("shmat");
        exit(1);
    }
    // Read from the shared memory
    printf("Reading from shared memory: \"%s\"\n", data);
    // Detach the shared memory
    if (shmdt(data) < 0)
    {
        perror("shmdt");
        exit(1);
    }
    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("shmctl");
        exit(1);
    }
    return 0;
}