#include <stdio.h>  // Standard input output header file
#include <fcntl.h>  // File control header file
#include <unistd.h> // Unix standard header file for system calls like read, write, close

int main(int argc, char *argv[3]) {
    int fd, i;
    char buf[2];
    fd = open(argv[1], O_RDONLY, 0777);  // Opens the file in read only mode
    
    // O_RDONLY - read only
    // 0777 represents all the permissions are granted of the file

    // If we won't give any file then argc will be 1(./a.out) and if we give file then argc will be 2(./a.out file_name)
    
    if (fd == -argc)   // -argc represents the error in opening the file    
    {
        printf("file open error");
    }
    else
    {
        while ((i = read(fd, buf, 1)) > 0)
        {
            printf("%c", buf[0]);
        }
        close(fd);
    }

    return 0;
}
