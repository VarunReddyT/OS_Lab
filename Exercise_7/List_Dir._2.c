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
        printf("Inode: %lu\t File: %s\n", entry->d_ino, entry->d_name);
    }
    closedir(dir);
    return EXIT_SUCCESS;
}