#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int res;

    // Open the FIFO for writing
    res = open("fifo1", O_WRONLY);
    if (res == -1) {
        perror("Failed to open FIFO for writing");
        exit(1);
    }

    // Write data to the FIFO
    if (write(res, "Message", 7) == -1) {
        perror("Failed to write to FIFO");
        close(res);
        exit(1);
    }

    printf("Sender Process %d sent the data\n", getpid());

    close(res);
    return 0;
}
