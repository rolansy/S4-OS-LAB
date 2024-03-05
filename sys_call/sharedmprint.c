#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

void main(){
    int i,fact;
    int fd=shm_open("/os_shm",O_RDONLY,0666);;
    int *data=(int *)mmap(NULL,sizeof(int),PROT_READ,MAP_SHARED,fd,0);
    int a=data[0];
    printf("Data read from shared memory : %d\n",a);
    munmap(data,sizeof(int));
    close(fd);
    shm_unlink("/os_shm");
}