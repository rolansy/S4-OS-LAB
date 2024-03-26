#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#define SHM_KEY 1234

typedef struct {
    int* data;
    int front, rear, size;
} Queue;

Queue* create_queue(int n) {
    int shmid = shmget(SHM_KEY, sizeof(Queue) + n * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    Queue* queue = (Queue*) shmat(shmid, NULL, 0);
    if ((int)queue == -1) {
        perror("shmat");
        exit(1);
    }

    queue->data = (int*)(queue + 1);
    queue->front = queue->rear = -1;
    queue->size = n;
    return queue;
}

void enqueue(Queue* queue, int item) {
    if ((queue->rear + 1) % queue->size == queue->front) {
        printf("Queue is full\n");
        return;
    }

    if (queue->front == -1)
        queue->front = 0;

    queue->rear = (queue->rear + 1) % queue->size;
    queue->data[queue->rear] = item;
}

int dequeue(Queue* queue) {
    if (queue->front == -1) {
        printf("Queue is empty\n");
        return -1;
    }

    int item = queue->data[queue->front];

    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % queue->size;

    return item;
}

void display(Queue* queue) {
    if (queue->front == -1) {
        printf("Queue is empty\n");
        return;
    }

    int i = queue->front;
    while (i != queue->rear) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % queue->size;
    }
    printf("%d\n", queue->data[i]);
}

void main (){
    int ch,x,n;
    printf("Enter the size of the queue\n");
    scanf("%d",&n);
    Queue *qu = create_queue(n);
    while(1){
        printf("Enter your choice\n");
        printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:printf("Enter the element to be inserted\n");
                    scanf("%d",&x);
                    enqueue(qu,x);
                    break;
            case 2:dequeue(qu);
                    break;
            case 3:display(qu);
                    break;
            case 4:exit(0);
                    break;
            default:printf("Invalid choice\n");
        }
    }
}