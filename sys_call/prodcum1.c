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
        #include <stdio.h>
        #include <stdlib.h>
        #include <sys/ipc.h>
        #include <sys/shm.h>
        #include <stdbool.h>

        #define SHM_KEY 1234

        typedef struct {
            int* buffer;
            int in, out, size;
        } SharedMemory;

        SharedMemory* create_shared_memory(int n) {
            int shmid = shmget(SHM_KEY, sizeof(SharedMemory) + n * sizeof(int), IPC_CREAT | 0666);
            if (shmid < 0) {
                perror("shmget");
                exit(1);
            }

            SharedMemory* shared_memory = (SharedMemory*) shmat(shmid, NULL, 0);
            if ((int)shared_memory == -1) {
                perror("shmat");
                exit(1);
            }

            shared_memory->buffer = (int*)(shared_memory + 1);
            shared_memory->in = shared_memory->out = 0;
            shared_memory->size = n;
            return shared_memory;
        }

        void enqueue(SharedMemory* shared_memory, int item) {
            if ((shared_memory->in + 1) % shared_memory->size == shared_memory->out) {
                printf("Buffer is full\n");
                return;
            }

            shared_memory->buffer[shared_memory->in] = item;
            shared_memory->in = (shared_memory->in + 1) % shared_memory->size;
        }

        int dequeue(SharedMemory* shared_memory) {
            if (shared_memory->in == shared_memory->out) {
                printf("Buffer is empty\n");
                return -1;
            }

            int item = shared_memory->buffer[shared_memory->out];
            shared_memory->out = (shared_memory->out + 1) % shared_memory->size;

            return item;
        }

        void display(SharedMemory* shared_memory) {
            if (shared_memory->in == shared_memory->out) {
                printf("Buffer is empty\n");
                return;
            }

            int i = shared_memory->out;
            while (i != shared_memory->in) {
                printf("%d ", shared_memory->buffer[i]);
                i = (i + 1) % shared_memory->size;
            }
            printf("\n");
        }

        void main (){
            int ch,x,n;
            printf("Enter the size of the buffer\n");
            scanf("%d",&n);
            SharedMemory *shm = create_shared_memory(n);
            while(1){
                printf("Enter your choice\n");
                printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\n");
                scanf("%d",&ch);
                switch(ch){
                    case 1:printf("Enter the element to be inserted\n");
                            scanf("%d",&x);
                            enqueue(shm,x);
                            break;
                    case 2:dequeue(shm);
                            break;
                    case 3:display(shm);
                            break;
                    case 4:exit(0);
                            break;
                    default:printf("Invalid choice\n");
                }
            }
        }
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