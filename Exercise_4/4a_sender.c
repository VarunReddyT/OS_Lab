#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
int res,n;
res=open("fifo1",O_WRONLY);
write(res,"IPC communication using named pipe",35);
printf("Sender Process %d sent the data\n",getpid());
}