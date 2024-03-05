#include <stdio.h>
#include <unistd.h>
void main(){
	fork();
	fork();
	fork();
	printf("h\n");
	fork();
}
