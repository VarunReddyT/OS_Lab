/*Alex Works as a systems administrator at DataSecure Inc., a company that deals 
with sensitive customer data. Recently, there have been concerns about
unauthorized access to critical system files and directories. 
To address this, Alex has decided to implement a monitoring solution that 
tracks the following information for each file:
1.	File type
2.	Number of links
3.	Read, write, and execute permissions
4.	Time of last access
Write a C implementation for the same by accepting one or more file or directory
names as command line input .*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("File not provided");
    }
    struct stat file_stat;
    if (stat(argv[1], &file_stat) == -1)
    {
        fprintf(stderr, "Error accessing %s\n", argv[1]);
        return 0;
    }
    printf("File Type: ");
    if (S_ISREG(file_stat.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(file_stat.st_mode))
        printf("Directory\n");
    else if (S_ISCHR(file_stat.st_mode))
        printf("Character Device\n");
    else if (S_ISBLK(file_stat.st_mode))
        printf("Block Device\n");
    else if (S_ISFIFO(file_stat.st_mode))
        printf("FIFO/Named Pipe\n");
    else if (S_ISLNK(file_stat.st_mode))
        printf("Symbolic Link\n");
    else if (S_ISSOCK(file_stat.st_mode))
        printf("Socket\n");
    else
        printf("Unknown\n");
     printf("Number of Links: %ld\n", (long)file_stat.st_nlink);
    printf("Permissions (rwx): ");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x\n" : "-\n");
    printf("Last Access Time: %s", ctime(&file_stat.st_atime));

    return 0;
}