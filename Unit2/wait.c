#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid,childpid;
    pid = fork();
    
    if(pid < 0){
        printf("Fork Failed");
        return 1;
    }
    else if(pid == 0){
        printf("Child Process : %d\n",getpid());
    }
    else{
        childpid = wait(NULL);
        printf("Exitted child process with id : %d\n",childpid);
        printf("Parent Process : %d\n",getpid());
    }
}