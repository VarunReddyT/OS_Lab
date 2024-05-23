#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int res, n;
    char buffer[100];

    // Open the FIFO for reading
    res = open("fifo1", O_RDONLY);
    if (res == -1) {
        perror("Failed to open FIFO for reading");
        exit(1);
    }

    // Read data from the FIFO
    n = read(res, buffer, sizeof(buffer) - 1);
    if (n == -1) {
        perror("Failed to read from FIFO");
        close(res);
        exit(1);
    }
    buffer[n] = '\0'; // Null-terminate the string

    printf("Reader Process %d received the data: %s\n", getpid(), buffer);

    close(res);
    return 0;
}
