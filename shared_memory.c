#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int in=-1,out=-1;
int buffer[5];

void consume();
void produce(int x);
void display();

int main(){
    int choice,item;
    do{
        printf("\n");
        printf("1.Produce\n2.Consume\n3.Display\n4.Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("\nEnter item to insert to buffer: ");
                    scanf("%d",&item);
                    produce(item);
                    break;
            case 2: consume();break;
            case 3: display();break;
            case 4: break;
            default: printf("\nInvalid Choice\n");
        }
    }while(choice!=4);
}

void consume(){
    if(in==-1){
        printf("Nothing to consume\n");
    }
    else{
        printf("Item consumed is: %d",buffer[in]);
        if(in==out){
            in=out=-1;
        }
        else{
            in=((in+1)%5);
        }
    }
}

void produce(int x){
    if(in==(out+1)%5){
        printf("Cannot prodice till consumer haves it\n");
    }
    else{
        if(in==-1){
            in=out=0;
        }
        else{
            out=((out+1)%5);
            
        }
        buffer[out]=x;
	printf("\nThe produced item is: %d",buffer[out]);
    }
}

void display(){
    int i;
    printf("\nThe buffer contains:\n");
    if(out>=in){
        for(i=in;i<=out;++i){
            printf(" - %d ",buffer[i]);
        }
    }
    else{
        for(i=in;i<5;++i){
            printf(" - %d ",buffer[i]);
        }
        for(i=0;i<=out;++i){
            printf(" - %d ",buffer[i]);
        }
    }
    printf("\n");
}
