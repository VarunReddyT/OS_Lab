#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

void deposit(int *balance , int amount){
    *balance += amount;
    printf("Depositing %d to account\n",amount);
    printf("New balance after withdrawal: %d\n",*balance);

}

void withdraw(int * balance , int amount){
    if(amount > *balance){
        printf("Insufficient funds\n");
        return;
    }
    *balance-=amount;
    printf("Withdrawing %d from account\n",amount);
    printf("New balance after withdrawal: %d\n",*balance);
}

int main()
{
    sem_t mutex;
    sem_init(&mutex, 0, 1); 

    // shared resource;
    int shm_fd = shm_open("/shared_balance", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Failed to create shared memory");
        exit(1);
    }

    // Set size of shared memory object
    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        perror("Failed to set size of shared memory");
        exit(1);
    }

    // Map shared memory object
    int *initialBalance = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (initialBalance == MAP_FAILED) {
        perror("Failed to map shared memory");
        exit(1);
    }
    *initialBalance = 1000;

    pid_t pid = fork();
    if(pid==0){
        sem_wait(&mutex);
        int amt = 500;
        deposit(initialBalance,amt);
        sem_post(&mutex);
    }
    else if (pid>0)
    {   
        sem_wait(&mutex);
        int amt = 200;
        withdraw(initialBalance,amt);
        sem_post(&mutex);

    }
    else{
        printf("Error: fork() failed\n");
    }
    

    return 0;
}

