#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
void print_file_info(char *filename)
{
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1)
    {
        fprintf(stderr, "Error accessing %s: %s\n", filename, strerror(errno));
        return;
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
    printf("Last Access Time: %s", ctime(&file_stat.st_atime));
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
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    if (pw != NULL)
        printf("Owner: %s\n", pw->pw_name);
    if (gr != NULL)
        printf("Group: %s\n", gr->gr_name);
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file/directory names>\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; ++i)
    {
        printf("File Information for: %s\n", argv[i]);
        print_file_info(argv[i]);
        printf("\n");
    }
    return 0;
}