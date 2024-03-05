#include <stdio.h>
#include <unistd.h>
void main(){
    __pid_t p;
    int i;
    p=fork();
    if (p==0){
        printf("Child process\n");
        for (i=0;i<10;i++){
            printf("%d\n",i);
        }
        printf("\n");
    }
    else if (p>0){
        printf("Parent process\n");
        for (i=10;i<20;i++){
            printf("%d\n",i);
        }
        printf("\n");
    }
}