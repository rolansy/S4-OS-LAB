#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void isort(int arr[], int n, int dir)
{
    int i, key, j;
    if (dir == 1)
    {
        for (i = 1; i < n; i++)
        {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
    else
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] < arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void fCFS(int head, int n, int arr[30])
{
    printf("Order = %d %d ", head, arr[0]);
    int time = abs(arr[0] - head);
    for (int i = 1; i < n; i++)
    {
        time += abs(arr[i] - arr[i - 1]);
        printf("%d ", arr[i]);
    }
    printf("\nSeek Time = %d\n\n", time);
    printf("\nAverage Seek Time = %d\n\n", time/n);
}

void sSTF(int head, int n, int arr[30])
{
    int processed[30] = {0};
    printf("Order = %d ", head);
    int time = 0;
    for (int count = 0; count < n; ++count)
    {
        int minDist = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < n; ++i)
        {
            if (!processed[i] && abs(arr[i] - head) < minDist)
            {
                minIndex = i;
                minDist = abs(arr[i] - head);
            }
        }
        if (minIndex == -1)
            break;
        printf("%d ", arr[minIndex]);
        time += minDist;
        head = arr[minIndex];
        processed[minIndex] = 1;
    }
    printf("\nSeek Time = %d\n", time);
    printf("\nAverage Seek Time = %d\n", time/n);
}


/*
void scan(int head, int n, int arr[30])
{
    int dir = 1;
    int siz, prev;
    printf("Enter the Size:");
    scanf("%d", &siz);
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
     if(dir==1)
    {ar1[0] =siz -1;
    n1 = 1;}
    else
    {ar2[0] = 0;
    n2 = 1;}
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("SCAN ORDER IS:\n");
    n2--;
    n1--;
    printf("%d ", head);
    if (dir == -1)
    {
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        ans += head - 0; 
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        printf("\n");
        printf("Seek Time = %d\n\n", ans);
    }
    else
    {
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        ans += siz - head;
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        printf("\n");
        printf("Seek Time = %d\n\n", ans-1);
        printf("Average Seek Time = %d\n\n", (ans-1)/siz);
    }
}
*/
/*
void scanq(int head, int Q[], int n, int tracks, int Di) {

    int scount = 0;

    

    // Sorting the queue of requests

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (Q[j] > Q[j + 1]) {

                int temp = Q[j];

                Q[j] = Q[j + 1];

                Q[j + 1] = temp;

            }

        }

    }

    

    int index = 0;

    for (int i = 0; i < n; i++) {

        if (head < Q[i]) {

            index = i;

            break;

        }

    }

    

    if (Di == 1) {

        for (int i = index; i < n; i++) {

            scount += abs(head - Q[i]);

            head = Q[i];

        }

        // Edge case handling: when the head is at the end of tracks

        if (index != 0)

            scount += abs(tracks - Q[n - 1] - 1);

        head = tracks - 1;

        for (int i = index - 1; i >= 0; i--) {

            scount += abs(head - Q[i]);

            head = Q[i];

        }

    } else {

        for (int i = index - 1; i >= 0; i--) {

            scount += abs(head - Q[i]);

            head = Q[i];

        }

        // Edge case handling: when the head is at the beginning of tracks

        if (index != n)

            scount += abs(Q[0] - 0);

        head = 0;

        for (int i = index; i < n; i++) {

            scount += abs(head - Q[i]);

            head = Q[i];

        }

    }

    printf("%d", scount);

}

*/

int scan() {

    int i,init,np,dir,temp,size,totalDisk,req[50];
    printf("Enter the number of process : ");
    scanf("%d",&np);
    printf("Enter the request sequence : ");
    for(i=0;i<np;i++){
        scanf("%d",&req[i]);
    }
    printf("Enter disk size : ");
    scanf("%d",&size);
    printf("Enter the initial disk position : ");
    scanf("%d",&init);
    printf("Enter direction of head (0 for left to right any other number for right to left) : ");
    scanf("%d",&dir);
    for(i=0;i<np;i++){
        for(int j=0;j<np-i-1;j++){
            if(req[j]>req[j+1]){
                temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    if(!dir){
        totalDisk=(size-init)+(size-req[0]);
    }
    else{
        totalDisk=(init+req[np-1]);
    }
    printf("The total disk movement : %d\n",totalDisk);
    return 0;

}

void cscan(int head, int n, int arr[30])
{
    int dir = 1, siz, prev;
    printf("Enter the Size:");
    scanf("%d", &siz);
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
    ar1[0] = siz - 1;
    n1 = 1;
    ar2[0] = 0;
    n2 = 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("CSCAN ORDER IS:\n");
    printf("%d ", head);
    if (dir == -1)
    {
        n2--;
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        for (int i = 0; i < n1; i++)
        {
            ans += abs(head - ar1[i]);
            printf("%d ", ar1[i]);
            head = ar1[i];
        }
    }
    else
    {
        n1--;
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        for (int i = 0; i < n2; i++)
        {
            ans += abs(head - ar2[i]);
            printf("%d ", ar2[i]);
            head = ar2[i];
        }
    }
    printf("\n");
    printf("Seek Time = %d\n\n", ans);
}

void look(int head, int n, int arr[30])
{
    int dir = 1, prev;
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("LOOK ORDER IS:\n");
    n2--;
    n1--;
    printf("%d ", head);
    if (dir == -1)
    {
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
    }
    else
    {
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
    }
    printf("\n");
    printf("Seek Time: %d\n\n", ans);
}

void clook(int head, int n, int arr[30])
{
    int dir = 1, prev;
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("CLOOK ORDER IS:\n");
    printf("%d ", head);
    if (dir == -1)
    {
        n2--;
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        for (int i = 0; i < n1; i++)
        {
            ans += abs(head - ar1[i]);
            printf("%d ", ar1[i]);
            head = ar1[i];
        }
    }
    else
    {
        n1--;
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        for (int i = 0; i < n2; i++)
        {
            ans += abs(head - ar2[i]);
            printf("%d ", ar2[i]);
            head = ar2[i];
        }
    }
    printf("\n");
    printf("Seek Time = %d\n\n", ans);
}


int main()
{
    int head, n;
    int arr[30];
    printf("DISK SCHEDULING ALGORITHMS\n\n");
    printf("Enter the current position...\n");
    scanf("%d", &head);
    printf("Enter the number of requests...\n");
    scanf("%d", &n);
    printf("Enter the requests...\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int op = 0;
    while (op != 7)
    {
        printf("\n\nEnter your option...\n1. FCFS\n2. SSTF\n3. SCAN\n4. CSCAN\n5. LOOK\n6. CLOOK\n7. Exit\n\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            fCFS(head, n, arr);
            break;
        case 2:
            sSTF(head, n, arr);
            break;
        case 3:
            scan();
            break;
        case 4:
            cscan(head, n, arr);
            break;
        case 5:
            look(head, n, arr);
            break;
        case 6:
            clook(head, n, arr);
            break;
        case 7:
            return 0;
            break;
        }
    }
}
