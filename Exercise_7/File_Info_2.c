#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int i, j;
    struct stat a;
    for (i = 1; i < argc; i++)
    {
        printf("\n%s", argv[i]);
        stat(argv[i], &a);
        if (S_ISDIR(a.st_mode))
        {
            printf("Is a directory\n");
        }
        else
        {
            printf("Is a regular file\n");
        }
        printf("\n FILE PROPERTIES \n");
        printf("Inode number:%d\n", a.st_ino);
        printf("No of links:%d\n", a.st_nlink);
        printf("Last access time:%s", asctime(localtime(&a.st_atime)));
        printf("permission Flag:%o\n", a.st_mode % 512);
        printf("size:%d\n", a.st_size);
    }
    return 0;
}