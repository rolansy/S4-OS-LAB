#include <stdio.h>


void input_processes(int m, int ps[]){
	for (int i=0; i<m; i++){
		printf("Enter Size of Process %d : ", i+1);
		scanf("%d", &ps[i]);
	}
}

void input_blocks(int n,int bs[]){
	for (int i=0;i<n;i++){
		printf("Enter Size of Block %d : ",i+1);
		scanf("%d",&bs[i]);
	}

}


void first_fit(int ps[100],int bs[100],int m,int n){
	int allocation[100];
	for (int i=0;i<m;i++){
		allocation[i]=-1;
	}
	for (int i=0;i<m;i++){
		for (int j=0;j<n;j++){
			if (bs[j]>=ps[i]){
				allocation[i]=j;
				bs[j]-=ps[i];
				break;
			}
		}
	}
	printf("\nProcess No.\tProcess Size\tBlock No.\n");
	for (int i=0;i<m;i++){
		printf("%d\t\t%d\t\t",i+1,ps[i]);
		if (allocation[i]!=-1){
			printf("%d\n",allocation[i]+1);
		}
		else{
			printf("Not Allocated\n");
		}
	}
}


void main(){
	int ch=0;	
	int ps[100];
	int bs[100];
	int m,n;
	while (ch!=10){
		printf("\n1.Input Processes\n2.Input Blocks\n3.First Fit\n10.Exit");
		printf("Enter Choice : ");
		scanf("%d",&ch);
		switch (ch){
			case 1: 
				printf("Enter number of processes : ");
				scanf("%d",&m);
				input_processes(m,ps);
				break;
			case 2: 
				printf("Enter number of blocks : ");
				scanf("%d",&n);
				input_blocks(n,bs);
				break;
			case 3: 
				first_fit(ps,bs,m,n);
				break;


			case 10: 
				break;
			default: 
				printf("Invalid Choice\n");
				break;
		}
	}


}


