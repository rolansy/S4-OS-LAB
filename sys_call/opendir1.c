#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
void main (){
    DIR *d;
    struct dirent *dir;
    d=opendir("yeet");
    if (d==NULL){
        printf("Directory not found\n");
    }
    else{
        printf("Directory found\n");
        closedir(d);
    }
}