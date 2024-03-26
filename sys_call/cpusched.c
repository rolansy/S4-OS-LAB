#include <stdio.h>
#include <stdlib.h>

typedef struct proc {
    int pid;
    int at;
    int bt;  
    int wt;
    int tat;
    int ct;
    int rt;
    int prio;
} proc;


void disptable(proc* procs,int n){
	printf("procs\tArrival Time\tBurst Time\tWaiting time\tTurnaround Time\tCompletion Time\tResponse Time\n");
	int totwt=0,tottat=0;
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].wt, procs[i].tat, procs[i].ct, procs[i].rt);
        totwt+=procs[i].wt;
        tottat+=procs[i].tat;
    }

    printf("Average waiting time = %f", totwt / (float)n);
    printf("\nAverage turn around time = %f \n", tottat /(float) n);

}

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
    printf("Sorted procs based on arrival time:\n");
    dispproc(procs, n);
}



void fcfs(proc* procs, int n) {
    int totwt = 0, tottat = 0;

    procs[0].wt = 0;
    procs[0].tat = 0;
	int time=0;
	procs[0].rt=0;
    for (int i = 0; i < n; i++) {
    	if( i==0){
    		procs[i].wt=0;
    		procs[i].rt=0;
    	}
    	else{
    		procs[i].wt=time-procs[i].at;
    		procs[i].rt=procs[i].wt-procs[i].at;
    	}
    	time+=procs[i].bt;
    	procs[i].tat=procs[i].bt+procs[i].wt;
    	procs[i].ct = procs[i].tat + procs[i].at;
    	printf("\n %d %d \n",time,procs[i].ct);
    	tottat+=procs[i].tat;
    	totwt+=procs[i].wt;
    	
    }
	printf("\nFCFS Schelduling\n");
	disptable(procs, n);
    
    
}


void sjf(proc* procs, int n) {
    
    proc temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(procs[i].bt > procs[j].bt) {
                temp = procs[i];
                procs[i] = procs[j];
                procs[j] = temp;
            }
        }
    }


    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < procs[i].at) {
            time = procs[i].at;
        }

        procs[i].rt = time - procs[i].at;
        procs[i].tat = procs[i].rt + procs[i].bt;
        procs[i].wt = procs[i].tat - procs[i].bt;

        time += procs[i].bt;
    }

    printf("\nSJF Scheduling:\n");
    disptable(procs, n);
}


void priority(proc* procs, int n) {

    proc temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (procs[j].prio > procs[j + 1].prio) {

                temp = procs[j];
                procs[j] = procs[j + 1];
                procs[j + 1] = temp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < procs[i].at) {
            time = procs[i].at;
        }

        procs[i].rt = time - procs[i].at;
        procs[i].tat = procs[i].rt + procs[i].bt;
        procs[i].wt = procs[i].tat - procs[i].bt;

        time += procs[i].bt;
    }

    printf("\nNon-Preemptive prio Scheduling:\n");
    disptable(procs, n);
}


void roundRobin(proc* procs, int n, int quantum) {
    int remBt[n]; //remainingbursttime
    for (int i = 0; i < n; i++) {
        remBt[i] = procs[i].bt;
    }

    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remBt[i] > 0) {
                int executeTime;
                if (remBt[i] > quantum) {
                    executeTime = quantum;
                } else {
                    executeTime = remBt[i];
                }
                if (time<procs[i].at){
                    procs[i].rt=0;
                }
                else{
                    procs[i].rt=time-procs[i].at;
                }
                time += executeTime;
                remBt[i] -= executeTime;

                if (remBt[i] == 0) {
                    completed++;
                    procs[i].tat = time - procs[i].at;
                    procs[i].wt = procs[i].tat - procs[i].bt;
                }
            }
        }
    }

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    disptable(procs, n);
}


void main(){
	int c,n,quantum;
	while (c!=10){
		printf("1. Input Process\n2. display\n3. Sort procs\n4. FCFS\n5. SJF\n6. Priority Scheduling\n7. Round Robin\n10.Exit\n");
		printf("Enter Choice : ");
		scanf("%d",&c);
		switch(c){
			case 1:
				printf("Enter Number of procs : ");
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
			case 5:
				sjf(procs,n);
				break;
			case 6:
				printf("Enter prio for each process:\n");
		        for (int i = 0; i < n; i++) {
		            printf("prio for process %d: ", i + 1);
		            scanf("%d", &procs[i].prio);
		        }
		        priority(procs, n);
		        break;
			case 7:
				printf("Enter time quantum for Round Robin: ");
		        scanf("%d", &quantum);
		        roundRobin(procs, n, quantum);
		        break;
		    default:
		        printf("Invalid choice\n");
				

				
			
		}
	}
}
