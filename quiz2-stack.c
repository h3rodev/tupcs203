// QUIZ 3 / Stack Operations
// Submitted by Ronald T. Tolentino
// TUP / CS203

/*
Instructions
Write the c programs for the Stack and Queue operations
stack operations 
Menu
Push
Pop
display
Exit
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

typedef struct stack
{
    int S[MAX];
    int top;
} STACK;
STACK S;

void makenull();
void push(int x);
void pop();
void makenull();
int isfull();
int isempty();
void display();
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
            system("cls");
            printf("Push Mode\n");
            printf("Input x: ");
            scanf("%d", &x);
            push(x);
            break;
        case 2:
            system("cls");
            printf("Pop Mode\n");
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:
            printf("\n1-4 only!\n");
            system("pause");
        }
    }
    return 0;
}

void makenull()
{
    S.top = MAX;
}

void push(int x)
{
    if (isfull())
    {
        printf("Stack Overflow.\n");
    }
    else
    {
        S.top--;
        S.S[S.top] = x;
    }
}

void pop()
{
    if (isempty())
    {
        printf("Stack is empty.\n");
    }
    else
    {
        printf("Top element removed.\n");
        S.top++;
    }
}

int isfull()
{
    return (S.top == 0);
}

int isempty()
{
    return (S.top == MAX);
}

void display()
{
    int i;
    if (!isempty())
    {
        printf("The stocks contains...\n");
        for (i = S.top; i < MAX; i++)
        {
            printf("%d.)%d\n", i + 1, S.S[i]);
        }
    }
    else
    {
        printf("No data to display.\n");
    }
}

int locate(int x)
{
    int i;
    for (i = 0; i <= S.top; i++)
    {
        if (x == S.S[i])
        {
            return i;
        }
    }
    return -1;
}

int menu()
{
    int op;

    printf("MENU\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Display\n");
    printf("4. Exit\n");
    printf("\nSelect(1-4): ");
    scanf("%d", &op);
    return (op);
}