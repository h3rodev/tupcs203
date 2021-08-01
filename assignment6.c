// Assingment 6
// Submitted by Ronald T. Tolentino
// TUP / CS203

/*
Instructions
Implement the student records (name, q1,q2,q3,ave,remarks) using pointer implementation of list
    Menu
    Insert
    Update
    Delete
    Display
    Exit
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct student
{
    char name[31];
    int quiz1, quiz2, quiz3;
    struct student *next;
} STUDENT;
STUDENT *S;

void insert(char n[31], int x, int y, int z);
void update(char n[31]);
int updatemenu();
void del(char n[31]);
void display();
int menu();
void save();
void retrieve();
void makenull();

int main()
{
    char nm[31];
    int a, b, c;
    makenull();
    retrieve();
    while (1)
    {
        switch (menu())
        {
        case 1:
            system("clear");
            printf("Insert Mode\n\n");
            printf("Name: ");
            scanf("%s", nm);
            printf("\nInput Quiz 1: ");
            scanf("%d", &a);
            printf("\nInput Quiz 2: ");
            scanf("%d", &b);
            printf("\nInput Quiz 3: ");
            scanf("%d", &c);
            insert(nm, a, b, c);
            break;
        case 2:
            system("clear");
            printf("Update Mode\n\n");
            printf("Input Students Name: ");
            scanf("%s", nm);
            update(nm);
            break;
        case 3:
            system("clear");
            printf("Delete Mode\n\n");
            printf("Input x: ");
            scanf("%s", nm);
            del(nm);
            break;
        case 4:
            display();
            break;
        case 5:
            save();
            exit(0);
        default:
            printf("1 to 5 only.\n");
            system("pause");
        }
    }

    return 0;
}
void insert(char n[31], int x, int y, int z)
{
    STUDENT *p, *q, *temp;
    p = q = S;
    temp = (STUDENT *)malloc(sizeof(STUDENT));
    strcpy(temp->name, n);
    temp->quiz1 = x;
    temp->quiz2 = y;
    temp->quiz3 = z;

    // locate the last element in list S
    while (p != NULL && strcmp(p->name, n) < 0)
    {
        q = p;
        p = p->next;
    }
    if (p == S)
        S = temp;
    else
        q->next = temp;

    temp->next = p;
}
void update(char n[31])
{
    STUDENT *p, *q;
    p = q = S;
    int ua, ub, uc;
    while (p != NULL && strcmp(p->name, n) != 0)
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        system("clear");
        printf("Update Mode\n");
        printf("Student: %s\n", p->name);
        printf("Quiz 1 Grade: %d\n", p->quiz1);
        printf("Quiz 2 Grade: %d\n", p->quiz2);
        printf("Quiz 3 Grade: %d\n\n", p->quiz3);
        while (1)
        {
            switch (updatemenu())
            {
            case 1:
                printf("Quiz 1 Grade:");
                scanf("%d", &ua);
                p->quiz1 = ua;
                break;
            case 2:
                printf("Quiz 2 Grade:");
                scanf("%d", &ub);
                p->quiz2 = ub;
                break;
            case 3:
                printf("Quiz 3 Grade:");
                scanf("%d", &uc);
                p->quiz3 = uc;
                break;
            case 0:
                save();
                main();
                break;
            default:
                printf("Select an option between 1 to 3\n");
                printf("or select 0 to exit the Update Menu: ");
            }
        }
    }
}
int updatemenu()
{
    int um;
    printf("Update Menu\n");
    printf("1.) Update Quiz 1 Grade\n");
    printf("2.) Update Quiz 2 Grade\n");
    printf("3.) Update Quiz 3 Grade\n");
    printf("0.) Return to the Main Menu\n");
    printf("Select an option between 1 to 3\n");
    printf("or select 0 to exit the Update Menu: ");
    scanf("%d", &um);
    return (um);
}

void del(char n[31])
{
    STUDENT *p, *q;
    p = q = S;
    while (p != NULL && strcmp(p->name, n) != 0)
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        if (p == S)
            S = p->next; //first element
        else
            q->next = p->next;
        free(p); //deallocate the memory space pointed to by p
        printf("%s deleted successfully.\n\n", p->name);
        system("pause");
    }
}
void display()
{
    STUDENT *p;
    p = S;
    int i = 1;
    system("clear");
    printf("No.\tNAME\tQuiz 1\tQuiz 2\tQuiz 3\tAverage\tRemarks\n");
    while (p != NULL)
    {
        float ave = (p->quiz1 + p->quiz2 + p->quiz3) / 3.0;
        printf("%d.)\t%s\t%d\t%d\t%d\t%6.2f\t%s\n", i++, p->name, p->quiz1, p->quiz2, p->quiz3, ave, ave >= 75 ? "PASSED" : "FAILED");
        p = p->next;
    }
    system("pause");
}
int menu()
{
    int op;
    printf("Menu\n");
    printf("1.) Insert\n");
    printf("2.) Update\n");
    printf("3.) Delete\n");
    printf("4.) Display\n");
    printf("5.) Exit\n");
    printf("\n\nSelect(1-5): ");
    scanf("%d", &op);
    return (op);
}
void save()
{
    FILE *fp;
    STUDENT *p;
    p = S;
    fp = fopen("studentsdb.txt", "w+");
    while (p != NULL)
    {
        fprintf(fp, "%s %d %d %d\n", p->name, p->quiz1, p->quiz2, p->quiz3);
        p = p->next;
    }
    fclose(fp);
}
void retrieve()
{
    FILE *fp;
    char n[31];
    int ax, by, cz;

    fp = fopen("studentsdb.txt", "r+");
    while (!feof(fp))
    {
        fscanf(fp, "%s %d %d %d\n", n, &ax, &by, &cz);
        insert(n, ax, by, cz);
    }
    fclose(fp);
}
void makenull()
{
    S = NULL;
}
