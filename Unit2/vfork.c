#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    pid_t p;
    p = vfork();
    if(p==0){
        printf("Child Process\n");
        printf("PID: %d\n",getpid());
        printf("Child process exitting with exit()\n");
        exit(0);
    }
    else if(p>0){
        printf("Parent Process\n");
        printf("PID: %d\n",getpid());
    }
    else{
        printf("Error\n");
    }
    return 0;
}