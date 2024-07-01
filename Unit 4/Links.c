#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<unistd.h>

int main(){
    const char * sourcefile = "source.txt";
    const char * hardlink = "hardlink.txt";
    const char * softlink = "shortcut";

    if(link(sourcefile,hardlink) == -1){
        perror("Error creating hard link");
        return 1;
    }
    printf("Hard link created : %s -> %s\n",hardlink,sourcefile);

    if(symlink(sourcefile,softlink) == -1){
        perror("Error creating soft link");
        return 1;
    }
    printf("Soft link created : %s -> %s\n",softlink,sourcefile);
    if(unlink(hardlink) == -1){
        perror("Error deleting hard link");
        return 1;
    }
    printf("File deleted : %s\n",sourcefile);

    return 0;
}