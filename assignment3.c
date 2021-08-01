// Assignment 3
// Submitted by Ronald T. Tolentino
// TUP / CS203

/* Instructions
    Modify assignment 2(name, q1, q2, q3) to use Menu
    Menu
    Insert record
    Delete record
    Display //tabular output including ave and remarks
    Exit
    Select(1 - 4) :
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

//Global Variables
char student[MAX][31];
int quiz1[MAX], quiz2[MAX], quiz3[MAX];
int last;

//Functions without return value
void initialize();
void add();
void del();
void display();

//Functions with return value
int menu();
int isfull();
int isempty();

//Functions with return value and parameters
int search(char sn[31]);
float getAverage(int q1, int q2, int q3);

int main()
{
    initialize();
    while (1)
    {
        switch (menu())
        {
        case 1:
            add();
            break;
        case 2:
            del();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Thank You For Using The Program...\n");
            printf("Exiting Now...\n");
            system("pause");
            exit(0);
        default:
            printf("1 to 4 Only.\n");
            system("pause");
        }
    }
    return 0;
}

void initialize()
{
    last = -1;
}

void add()
{
    char sn[31];
    int q1, q2, q3;

    if (isfull())
    {
        system("cls");
        printf("Add Student Mode\n");
        printf("Array Is Full!.\n");
        printf("Please Select Other Menu Option.\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("Add Student Mode\n");
        printf("Input Name: ");
        scanf("%s", sn);
        printf("Input QUIZ 1: ");
        scanf("%d", &q1);
        printf("Input QUIZ 2: ");
        scanf("%d", &q2);
        printf("Input QUIZ 3: ");
        scanf("%d", &q3);

        last = last + 1;
        strcpy(student[last], sn);
        quiz1[last] = q1;
        quiz2[last] = q2;
        quiz3[last] = q3;
        printf("Student Records Added\n");
        system("pause");
    }
}

void del()
{
    char sn[31];
    int i, p;
    if (isempty())
    {
        printf("DELETE MODE\n");
        printf("Array Is Empty.\n");
        printf("There Is Nothing To Delete.\n");
        printf("Please Select Other Menu Option.\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("DELETE MODE\n");
        printf("Input Student Name: ");
        scanf("%s", sn);

        p = search(sn);
        if (p == -1)
        {
            printf("DELETE MODE\n");
            printf("%s cannot be found.\n", sn);
            printf("Please try again.\n");
            system("pause");
        }
        else
        {
            for (i = p; i < last; i++)
            {
                strcpy(student[i], student[i + 1]);
                quiz1[i] = quiz1[i + 1];
                quiz2[i] = quiz2[i + 1];
                quiz3[i] = quiz3[i + 1];
            }
            printf("DELETE MODE\n");
            printf("%s is now deleted..\n", sn);
            system("pause");
            last--;
        }
    }
}

int search(char sn[31])
{
    int i;
    for (i = 0; i <= last; i++)
        if (strcmp(student[i], sn) == 0)
            return i;
    return -1;
}

void display()
{
    if (isempty())
    {
        system("cls");
        printf("DISPLAY MODE\n");
        printf("Array is empty...\n");
        printf("There is nothing to display...\n");
        printf("Please Select Other Menu Option...\n");
        system("pause");
    }
    else
    {
        int i;
        float ave;
        system("cls");
        printf("DISPLAY MODE\n");
        printf("No.  NAME   Quiz 1    Quiz 2    Quiz 3    Average   Remarks\n");
        for (i = 0; i <= last; i++)
        {
            ave = getAverage(quiz1[i], quiz2[i], quiz3[i]);
            printf("%d.)  %s     %d      %d      %d      %6.2f   %s\n", i + 1, student[i], quiz1[i], quiz2[i], quiz3[i], ave, ave >= 75 ? "Passed" : "Failed");
        }
        system("pause");
    }
}

int menu()
{
    int m;
    system("cls");
    printf("Menu\n");
    printf("1.) Insert record\n");
    printf("2.) Delete record\n");
    printf("3.) Display\n");
    printf("4.) Exit\n");
    printf("Select(1-4): ");
    scanf("%d", &m);
    return (m);
}

float getAverage(int q1, int q2, int q3)
{
    float ave = (q1 + q2 + q3) / 3.0;
    return ave;
}

int isfull()
{
    return (last == MAX - 1);
}
int isempty()
{
    if (last == -1)
        return 1;
    else
        return 0;
}
