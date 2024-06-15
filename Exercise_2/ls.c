#include<stdio.h>
#include<dirent.h>   // directory manipulation functions.

int main(){
    DIR * dir = opendir(".");      //  If successful, opendir returns a pointer to a DIR structure representing the directory, which is assigned to dir. If it fails, it returns NULL.
    if(dir == NULL){
        printf("Error opening directory");
        return 1;
    }

    struct dirent * entry;    // declares a pointer to a struct dirent, which represents a directory entry. It will be used to store information about each directory entry as we traverse the directory.
    while((entry = readdir(dir))!=NULL){
        printf("%s\n",entry->d_name);
    }
    closedir(dir);
    return 0;
}