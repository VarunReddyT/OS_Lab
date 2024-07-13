/*Alice is a system administrator at a large company. 
Recently, she has noticed that the server's storage is filling up quickly, and 
she suspects there might be some large files hidden deep within the directory structure 
that are taking up a lot of space. To identify these files, Alice wants to list 
all files along with their inode numbers and file names. 
decides to write a C program for this purpose.*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    if (argc < 2)
    {
        dir = opendir(".");
    }
    else
    {
        dir = opendir(argv[1]);
    }
    if (dir == NULL)
    {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
        if (stat(path, &file_stat) == -1)
        {
            perror("Error stat");
            continue;
        }
        printf("Inode: %lu\t File: %s\n", file_stat.st_ino, entry->d_name);
    }
    closedir(dir);
    return EXIT_SUCCESS;
}