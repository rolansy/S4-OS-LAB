#include<stdio.h>
#include<string.h>

int q[100],front=-1,rear=-1;

struct process
{
  char name[20];
  int at,tt,bt,wt,ct,status,left,pr;
}p[20],temp;

struct done
{
  char name[20];
  int st,ct;
}d[20];

void enqueue(int j)
{
  if(front==-1 && rear==-1)
  {
    front++;
  }
  rear++;
  q[rear] = j;
}
int dequeue()
{
  int item;
  item = q[front];
  if(front == rear)
  {
    front = -1;
    rear = -1;
  }
  else
  {
    front++;
  }
  return(item);
}
void roundrobin()
{
  int n,i,j,idle=0,k,num,ls,t;
  float avwt=0,avtt=0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    p[i].left = p[i].bt;
    p[i].status = 0;
  }
  printf("\nENTER THE TIME QUANTUM : ");
  scanf("%d",&t);

  for(i=0,num=0,ls=0;ls<n;)
  {
    for(j=0;j<n;j++)
    {
      if(p[j].status==0 && p[j].at<=i)
      {
        enqueue(j);
        p[j].status = 1;
      }
    }
    if(idle==0 && front == -1)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      idle = 1;
      i++;
    }
    else if(front!=-1)
    {
      if(idle==1)
      {
        d[num].ct = i;
        idle = 0;
        num++;
      }
      k = dequeue();
      d[num].st = i;
      strcpy(d[num].name,p[k].name);
      if(p[k].left<=t)
      {
        d[num].ct = i+p[k].left;
        p[k].ct = d[num].ct;
        i = d[num].ct;
        p[k].tt = i - p[k].at;
        p[k].wt = p[k].tt - p[k].bt;
        p[k].status = 2;
        ls++;
        num++;
      }
      else if(p[k].left>t)
      {
        d[num].ct = i+t;
        i = d[num].ct;
        p[k].left = p[k].left-t;
        num++;
        for(j=0;j<n;j++)
        {
          if(p[j].status==0 && p[j].at<=i)
          {
            enqueue(j);
            p[j].status = 1;
          }
        }
        enqueue(k);
      }
    }
    else
    {
      i++;
    }
  }

  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    avwt+=p[i].wt;
    avtt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t",d[num-1].ct);
  printf("\n\nAVERAGE WAITING TIME : %f",(avwt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(avtt/n));
}

void priority()
{
  int n,i,j,ls,min,fnd,num,idle;
  float twt=0.0,ttt=0.0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    printf("PRIORITY : ");
    scanf("%d",&p[i].pr);
    p[i].status = 0;
  }
  for(i=0,ls=0,num=0,idle=0;ls<n;)
  {
    for(j=0,fnd=0;j<n;j++)
    {
      if(i>=p[j].at && p[j].status==0)
      {
        if(fnd==0)
        {
          min = j;
          fnd = 1;
        }
        else if((p[min].pr>p[j].pr)||(p[min].pr==p[j].pr && p[min].at>p[j].at))
        {
          min = j;
        }
      }
    }
    if(idle==0 && fnd==0)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      i++;
      idle = 1;
    }
    else if(fnd==1)
    {
      if(idle==1)
      {
        d[num].ct = i;
        num++;
        idle = 0;
      }
      strcpy(d[num].name,p[min].name);
      p[min].status =1;
      d[num].st = i;
      d[num].ct = i + p[min].bt;
      i = d[num].ct;
      p[min].ct = d[num].ct;
      p[min].tt = p[min].ct - p[min].at;
      p[min].wt = p[min].tt - p[min].bt;
      num++;
      ls++;
    }
    else
    {
      i++;
    }
  }
  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    twt+=p[i].wt;
    ttt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t\n",d[num-1].ct);
  printf("\nAVERAGE WAITING TIME : %f",(twt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(ttt/n));
}

void sjf()
{
  int n,i,j,ls,min,fnd,num,idle;
  float twt=0.0,ttt=0.0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    p[i].status = 0;
  }
  for(i=0,ls=0,num=0,idle=0;ls<n;)
  {
    for(j=0,fnd=0;j<n;j++)
    {
      if(i>=p[j].at && p[j].status==0)
      {
        if(fnd==0)
        {
          min = j;
          fnd = 1;
        }
        else if(fnd!=0 && p[min].bt>p[j].bt)
        {
          min = j;
        }
      }
    }
    if(idle==0 && fnd==0)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      i++;
      idle = 1;
    }
    else if(fnd==1)
    {
      if(idle==1)
      {
        d[num].ct = i;
        num++;
        idle = 0;
      }
      strcpy(d[num].name,p[min].name);
      p[min].status =1;
      d[num].st = i;
      d[num].ct = i + p[min].bt;
      i = d[num].ct;
      p[min].ct = d[num].ct;
      p[min].tt = p[min].ct - p[min].at;
      p[min].wt = p[min].tt - p[min].bt;
      num++;
      ls++;
    }
    else
    {
      i++;
    }
  }
  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    twt+=p[i].wt;
    ttt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t\n",d[num-1].ct);
  printf("\nAVERAGE WAITING TIME : %f",(twt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(ttt/n));
}

void fcfs()
{
  int i,j,n,num,idle=0;
  float avwt=0;
  float avtt=0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    p[i].status = 0;
  }
  for(i=0;i<n;i++)                       //Sorting based on at
  {
    for(j=0;j<n-i-1;j++)
    {
      if(p[j].at > p[j+1].at)
      {
        temp = p[j];
        p[j] = p[j+1];
        p[j+1] = temp;
      }
    }
  }
  for(i=0,j=0,num=0;j<n;)              //Calculations
  {
    if(p[j].at<=i && p[j].status==0)
    {
      if(idle==1)
      {
        d[num].ct=i;
        num++;
        idle = 0;
      }
      strcpy(d[num].name,p[j].name);
      d[num].st = i;
      d[num].ct = i + p[j].bt;
      p[j].wt = d[num].st - p[j].at;
      p[j].tt = p[j].wt + p[j].bt;
      p[j].ct = d[num].ct;
      i = d[num].ct;
      p[j].status = 1;
      j++;
      num++;

    }
    else if(idle == 0)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      i++;
      idle = 1;
    }
    else
    {
      i++;
    }
  }
  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n");
  for(int i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    avwt+=p[i].wt;
    avtt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n----------------------------------------------------------\n");
      for(i=0;i<num;i++)
      {
          printf("|");
          printf("   %s\t",d[i].name);
       }
       printf(" |");
       printf("\n----------------------------------------------------------\n");
       for(i=0;i<num;i++)
       {
          printf("%d\t",d[i].st);
       }
       printf("%d\t",d[num-1].ct);
  printf("\n\nAVERAGE WAITING TIME : %f",(avwt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(avtt/n));
}

int main(){
    int choice;
    while(choice!=5){
        printf("\n");
        printf("1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\n5.Exit\nEnter choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1: fcfs();break;
            case 2: sjf();break;
            case 3: priority();break;
            case 4: roundrobin();break;
            case 5: break;
            default: printf("\nInvalid Choice\n");break;
        }
    }
}
