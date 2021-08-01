// QUIZ 3 / Queue Operations
// Submitted by Ronald T. Tolentino
// TUP / CS203

/*
Instructions
Write the c programs for the Stack and Queue operations
Queue operations
Enqueue
Dequeue
Display
Exit
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3
typedef struct queue
{
    int queue[MAX];
    int rear;
    int front;
} QUEUE;
QUEUE Q;

void enqueue();
void dequeue();
void display();
void makenull();

int isfull();
int isempty();
int menu();

int main()
{
    int x;
    makenull();
    while (1)
    {
        switch (menu())
        {
        case 1:
            printf("Enter Number: ");
            scanf("%d", &x);
            enqueue(x);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:
            printf("Choose from 1 to 4 only.\n");
            break;
        }
    }
}

void enqueue(x)
{
    if (Q.rear == MAX - 1)
    {
        printf("Queue Overflow...\n");
    }
    else
    {
        if (Q.front == -1)
        {
            Q.front = 0;
        }

        Q.rear = Q.rear + 1;
        Q.queue[Q.rear] = x;
    }
}
void dequeue()
{
    if (Q.front == -1)
    {
        printf("Queue Underflow.\n");
    }
    else
    {
        printf("Number %d dequeue from queue\n", Q.queue[Q.front]);
        if (Q.front == Q.rear)
        {
            Q.front = -1;
            Q.rear = -1;
        }
        else
        {
            Q.front = Q.front + 1;
        }
    }
}
void display()
{
    int i;
    if (Q.front == -1)
    {
        printf("Queue is empty...\n");
    }
    else
    {
        printf("QUEUE Data: \n");
        for (i = Q.front; i <= Q.rear; i++)
        {
            printf("%d.) %d\n", i + 1, Q.queue[i]);
        }
    }
}

int menu()
{
    int choice;
    printf("Menu\n");
    printf("1.)  enqueue\n");
    printf("2.)  dequeue\n");
    printf("3.)  Display\n");
    printf("4.)  Exit\n");

    printf("Choose 1-4 ");
    scanf("%d", &choice);
    return choice;
}

void makenull()
{
    Q.front = -1;
    Q.rear = -1;
}

int isfull()
{
    return (Q.rear == MAX - 1);
}
int isempty()
{
    return (Q.front == -1 && Q.rear == -1);
}