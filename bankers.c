#include <stdio.h>

void main(){
	int n,m,i,j,k,y,alloc[20][20],max[20][20],avail[50],ind=0;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
	printf("Enter the number of resources: ");
    scanf("%d",&m);
    printf("Enter the allocation matrix: ");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("Enter the max matrix: ");
    for (i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter Available Matrix  : ");
    for(i=0;i<m;i++){
        scanf("%d",&avail[i]);  
    }
    int finish[n],need[n][m],safe[n];
    
    for (i=0;i<n;i++){
        finish[i]=0;
    }

    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    printf("Need Matrix\n");
    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    for (i=0;i<n;i++){
        finish[i]=0;
    }


    for (k=0;k<n;k++){
        for (i=0;i<n;i++){
            if (finish[i]==0){
                int flag=0;
                for (j=0;j<m;j++){
                    if (need[i][j]>avail[j]){
                        flag=1;
                        break;
                    }
                }
                if (flag==0){
                    safe[ind++]=i;
                    for (y=0;y<m;y++){
                        avail[y]+=alloc[i][y];
                    }
                    finish[i]=1;
                }
            }
        }
    }
    if (ind==n){
        printf("Safe Sequence\n");
        for (i=0;i<n;i++){
            printf("P%d ",safe[i]);
        }
    }
    else{
        printf("Unsafe State\n");
    }
    printf("\n");

}
