#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main()
{
    int semaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    struct sembuf sem_op;

    if (semaphore < 0)
    {
        perror("Semaphore creation failed");
        exit(1);
    }
    printf("Semaphore created successfully.\n");

    // Initialize semaphore value to 1
    if (semctl(semaphore, 0, SETVAL, 1) == -1)
    {
        perror("Failed to initialize semaphore");
        exit(1);
    }

    sem_op.sem_num = 0;
    sem_op.sem_op = -1; // Lock the semaphore
    sem_op.sem_flg = 0;
    if (semop(semaphore, &sem_op, 1) == -1)
    {
        perror("Failed to lock semaphore");
        exit(1);
    }
    printf("Semaphore locked.\n");

    // Critical Section - Access shared resources here
    printf("In critical section.\n");

    sem_op.sem_op = 1; // Unlock the semaphore
    if (semop(semaphore, &sem_op, 1) == -1)
    {
        perror("Failed to unlock semaphore");
        exit(1);
    }
    printf("Semaphore unlocked.\n");

    if (semctl(semaphore, 0, IPC_RMID) == -1)
    {
        perror("Failed to remove semaphore");
        exit(1);
    }
    printf("Semaphore removed.\n");

    return 0;
}
