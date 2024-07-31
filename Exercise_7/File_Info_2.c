#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int i, j;
    struct stat a;
    for (i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
        stat(argv[i], &a);
        if (S_ISDIR(a.st_mode))
        {
            printf("is a directory\n");
        }
        else
        {
            printf("is a regular file\n");
        }
        printf("FILE PROPERTIES \n");
        printf("Inode number:%d\n", a.st_ino);
        printf("No of links:%d\n", a.st_nlink);
        printf("Last access time:%s", ctime(&a.st_atime));
        printf("Permission Flag:%o\n", a.st_mode % 512);
        printf("Size:%d\n", a.st_size);
    }
    return 0;
}