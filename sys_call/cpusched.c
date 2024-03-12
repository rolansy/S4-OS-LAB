#include <stdio.h>
#include <stdlib.h>

typedef struct proc {
    int pid;
    int at;
    int bt;  
} proc;

proc* createproc(int n) {
    proc* proces = (proc*)malloc(n * sizeof(proc));
    for(int i = 0; i < n; i++){
        proces[i].pid = i+1;
        printf("Enter Arrival time of proc %d : ",i+1);
        scanf("%d",&proces[i].at);
        printf("Enter Burst time of proc %d : ",i+1);
        scanf("%d",&proces[i].bt);
    }
    return proces;
}

void dispproc(proc* procs, int n){
    printf("PID\tArrival Time\tBurst Time\n");
    for(int i=0; i<n; i++){
        printf("%d\t%12d\t%10d\n", procs[i].pid,procs[i].at, procs[i].bt);
    }
}

void sortproc(proc* procs, int n) {
    proc temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(procs[i].at > procs[j].at) {
                temp = procs[i];
                procs[i] = procs[j];
                procs[j] = temp;
            }
        }
    }
    printf("Sorted processes based on arrival time:\n");
    dispproc(procs, n);
}

void fcfs(proc* procs, int n) {
    int wt[n], tat[n], ct[n], rt[n], totwt = 0, tottat = 0;

    wt[0] = 0;
    tat[0] = 0;
	int time=0;
	rt[0]=0;
    for (int i = 0; i < n; i++) {
    	if( i==0){
    		wt[i]=0;
    		rt[i]=0;
    	}
    	else{
    		wt[i]=time-procs[i].at;
    		rt[i]=wt[i]-procs[i].at;
    	}
    	time+=procs[i].bt;
    	tat[i]=procs[i].bt+wt[i];
    	ct[i] = tat[i] + procs[i].at;
    	printf("\n %d %d \n",time,ct[i]);
    	tottat+=tat[i];
    	totwt+=wt[i];
    	
    }

    
    printf("Processes\tArrival Time\tBurst Time\tWaiting time\tTurnaround Time\tCompletion Time\tResponse Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", procs[i].pid, procs[i].at, procs[i].bt, wt[i], tat[i], ct[i], rt[i]);
    }

    printf("Average waiting time = %f", totwt / (float)n);
    printf("\nAverage turn around time = %f \n", tottat /(float) n);
}

void main(){
	int c,n;
	while (c!=5){
		printf("1. Input Process\n2. display\n3. Sort Processes\n4. FCFS\n5.Exit\n");
		printf("Enter Choice : ");
		scanf("%d",&c);
		switch(c){
			case 1:
				printf("Enter Number of processes : ");
				scanf("%d", &n);
				proc* procs = createproc(n);
				break;
			case 2:
				dispproc(procs,n);
				break;
       	 	case 3:
       	 		sortproc(procs,n);
       	 		break;
       	 	
       	 	case 4:
				fcfs(procs,n);
				break;

				
			
		}
	}
}
