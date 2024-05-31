#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid==0){
        printf("Hello I am child process\n");
    }
    else if(pid>=0){
        printf("Hello I am Parent process\n");
    }
    else{
        printf("error : %d",getpid());
    }
}