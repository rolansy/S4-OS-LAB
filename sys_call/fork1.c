#include <stdio.h>
#include <unistd.h>

void main(){
    __pid_t pid;
    printf("Before fork\n");
    pid = fork();
    printf("%d\n",pid);
    if(pid == 0){
        printf("Child process\n");
    }
    else if (pid >0 ){
        printf("Parent process\n");
    }
    printf("Both processes continue from here\n");
}


