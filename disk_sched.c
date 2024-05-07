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
}

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
    }
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
            scan(head, n, arr);
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
