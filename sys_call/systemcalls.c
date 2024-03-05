#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void main(){
    __pid_t p;
    p=fork();
    if (p<0){
        printf("Fork Failed\n");
        return ;
        exit(EXIT_FAILURE);
    }
    else if (p==0){
        int status;
        wait(&status);
        sleep(1);
        printf("Child Process, PID : %d\n",getpid());
        char *args[] = {"/bin/ls", "-l", NULL};
        execvp(args[0], args);
        perror("execvp");
        return 1;
    
    }
    else{
        printf("Parent Process, PID : %d\n",getpid());
        printf("Waiting for child process : PID of child : %d\n",p);
        int status;
        wait(&status);
        sleep(2);

        DIR *d;
        struct dirent *dir;
        d=opendir(".");
        if (d==NULL){
            printf("Could not open current directory\n");
            return 0;
        }
        else if (d){ 
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current working dir: %s\n", cwd);
            }
            while ((dir=readdir(d))!=NULL){
                printf("%s\n",dir->d_name);
            }
            closedir(d);
        }
    }

}
