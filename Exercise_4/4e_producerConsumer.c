#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>


#define SEM_PRODUCER "/semProducer"
#define SEM_CONSUMER "/semConsumer"
int main()
{
        sem_t *semProducer, *semConsumer;

    // Initialize semaphores
    semProducer = sem_open(SEM_PRODUCER, O_CREAT, 0644, 1); 
    semConsumer = sem_open(SEM_CONSUMER, O_CREAT, 0644, 0); 
      if (semProducer == SEM_FAILED || semConsumer == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }
    pid_t p;
 
    p = fork();
    if (p > 0) // parent
    {   
        for (int i = 0; i < 5; i++)
        { 
              
            
            sem_wait(semProducer);
            printf("Producing Item : %d\n",i);
            sem_post(semConsumer);/* code */
            sleep(2);

        }
            wait(NULL);
        sem_close(semProducer);
        sem_close(semConsumer);
        sem_unlink(SEM_PRODUCER);
        sem_unlink(SEM_CONSUMER);
        
    }
    else // child
    {   
        for (int i = 0; i < 5; i++)
        {   
            sem_wait(semConsumer);
            printf("Consuming item : %d\n",i);
            sem_post(semProducer);
            sleep(2);
          
        }
        
    }
}