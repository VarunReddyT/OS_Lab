#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid = fork();

    if(pid<0){
        printf("Fork failed");
    }
    else if(pid == 0){
        printf("Child Process : %d\n",getpid());
    }
    else{
        printf("Parent Process : %d\n",getpid());;
    }
    return 0;
}