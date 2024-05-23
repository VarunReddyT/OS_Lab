#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    int res;
    res = mkfifo("fifo1",0777);
    printf("named pipe created\n");
    return 0;
}