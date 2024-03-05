#include <stdio.h>
#include <unistd.h>
void main(){
    __pid_t p;
    p=fork();
    if (p==0){
        printf("Child process\n");
        printf("PID of Child's Parent : %d\n",getppid());
        printf("PID of process : %d\n",getpid());
    }
    else if (p>0){
        printf("Parent process\n");
        printf("PID pf Parents's process : %d\n",getppid());
        printf("PID of process : %d\n",getppid());
    }
}