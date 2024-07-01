#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int res;
    res = open("fifo1", O_WRONLY);
    if (res == -1) {
        printf("Error opening FIFO");
        return 1;
    }
    write(res, "Hello World", 12);
    printf("Sender Process %d sent the data\n", getpid());
    close(res);
    return 0;
}
