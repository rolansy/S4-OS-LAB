#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

void main(){
    int fd=shm_open("/os_shm",O_CREAT|O_RDWR,0666);
    //open for reading and writing Ordwr
    int ft=ftruncate(fd,4096);
    
    if (ft==-1){
        printf("Shared Memory Failed\n");
    }
    else{
        printf("Shared memory succesffuly created\n");
        int *data=(int *)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        printf("Enter the numeber : ");
        scanf("%d",&data[0]);
        mmap(data,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        printf("Data written in shared memory\n");
        printf("Data written in shared memory : %d\n",data[0]);

    }
    close(fd);
}