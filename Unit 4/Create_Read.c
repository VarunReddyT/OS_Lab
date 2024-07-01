#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

int main(){
    int n, fd;
    char buf[50];
    printf("Enter the text:\n");
    n = read(0, buf, 50);
    fd = open("firstfile",O_CREAT|O_RDWR, 0777);
    write(fd, buf, n);
    write(1,buf,n);
    close(fd);
    return 0;
}