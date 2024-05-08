#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
    pid_t pids[2],wpid;
    pids[0] = fork();
    if(pids[0]==0){
        printf("First Child Process : PID : %d\n",getpid());
        printf("First child process exitting\n");
        exit(0);
    }
    pids[1] = fork();
    if(pids[1]==0){
        printf("Second Child Process : PID : %d\n",getpid());
        printf("Second child process exitting\n");
        // exit(0);
    }
    if(pids[0]>0 && pids[1]>0){
        wpid = waitpid(pids[1],NULL,0);
        printf("Parent : Proceeding after the second child with pid = %d has finished \n",pids[1]);
    }
    return 0;
}