// QUIZ 1
// Submitted by Ronald T. Tolentino
// TUP / CS203

/* Instructions
Modify assignment 3 to include saving, retrieving and updating of records.
MENU
INSERT RECORD
UPDATE RECORD (Using name as search key)
DELETE RECORD
DISPLAY
EXIT
SELECT(1-5):
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

//Global Variables
char student[MAX][31];
int quiz1[MAX], quiz2[MAX], quiz3[MAX];
int last;

//Functions without return value
void initialize();
void add(char sn[31], int qa, int qb, int qc);
void update(char sn[31]);
void del(char sn[31]);
void display();

//Functions with return value
int menu();
int updatemenu();
int isfull();
int isempty();
void save();
void retrieve();

//Functions with return value and parameters
int search(char sn[31]);
float getAverage(int q1, int q2, int q3);

int main()
{
    char sn[31];
    int qa, qb, qc;

    initialize();
    retrieve();
    while (1)
    {
        switch (menu())
        {
        case 1:
            system("clear");
            printf("Add Student Mode\n");
            printf("Enter Name: ");
            scanf("%s", sn);
            printf("Enter QUIZ 1: ");
            scanf("%d", &qa);
            printf("Enter QUIZ 2: ");
            scanf("%d", &qb);
            printf("Enter QUIZ 3: ");
            scanf("%d", &qc);
            add(sn, qa, qb, qc);
            break;
        case 2:
            system("clear");
            printf("UPDATE MODE\n");
            printf("Enter Student Name: ");
            scanf("%s", sn);
            update(sn);
            break;
        case 3:
            system("clear");
            printf("DELETE MODE\n");
            printf("Enter Student Name: ");
            scanf("%s", sn);
            del(sn);
            break;
        case 4:
            display();
            break;
        case 5:
            save();
            exit(0);
        default:
            printf("1 to 5 Only.\n");
            system("pause");
        }
    }
    return 0;
}

// Initialize the "last" pointer value.
void initialize()
{
    last = -1;
}

// Add new Student Name and Quizes.
void add(char sn[31], int qa, int qb, int qc)
{

    if (isfull())
    {
        system("clear");
        printf("Add Student Mode\n");
        printf("Array Is Full!.\n");
        printf("Please Select Other Menu Option.\n");
        system("pause");
    }
    else
    {
        last = last + 1;
        strcpy(student[last], sn);
        quiz1[last] = qa;
        quiz2[last] = qb;
        quiz3[last] = qc;
        printf("Student Records Added\n");
    }
}

// Update Quizes using the students name.
void update(char sn[31])
{
    int p, uq1, uq2, uq3;
    if (isempty())
    {
        printf("UPDATE MODE\n");
        printf("Array Is Empty.\n");
        printf("There Is Nothing To Update.\n");
        printf("Please Select Other Menu Option.\n");
        system("pause");
    }
    else
    {
        p = search(sn);
        if (p == -1)
        {
            printf("UPDATE MODE\n");
            printf("%s cannot be found.\n", sn);
            printf("Please try again.\n");
            system("pause");
        }
        else
        {

            while (1)
            {
                printf("UPDATE MODE\n");
                printf("Student: %s\n", student[p]);
                printf("QUIZ 1: %d\n", quiz1[p]);
                printf("QUIZ 2: %d\n", quiz2[p]);
                printf("QUIZ 3: %d\n", quiz3[p]);
                switch (updatemenu())
                {
                case 1:
                    printf("QUIZ 1:");
                    scanf("%d", &uq1);
                    quiz1[p] = uq1;
                    break;
                case 2:
                    printf("QUIZ 2:");
                    scanf("%d", &uq2);
                    quiz2[p] = uq2;
                    break;
                case 3:
                    printf("QUIZ 3:");
                    scanf("%d", &uq3);
                    quiz3[p] = uq3;
                    break;
                case 0:
                    // Call the save function to save all the updates before returning to main menu
                    // To make sure all data are up to date.
                    save();
                    main();
                    break;
                default:
                    printf("1 to 3 or 0 to exit update menu.\n");
                    system("pause");
                }
            }
        }
    }
}

// Remove records using the students name.
void del(char sn[31])
{
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

// Search records using the students name.
int search(char sn[31])
{
    int i;
    for (i = 0; i <= last; i++)
        if (strcmp(student[i], sn) == 0)
            return i;
    return -1;
}

// saving contents of arrays into a text file
void save()
{
    FILE *fp;
    int i;
    fp = fopen("studentsdb.txt", "w+");
    if (fp == NULL)
    {
        printf("File Error.\n");
        system("pause");
    }
    else
    {
        for (i = 0; i <= last; i++)
            fprintf(fp, "%s %d %d %d\n", student[i], quiz1[i], quiz2[i], quiz3[i]);
    }

    printf("File Is Saved/Updated...\n");
    system("pause");
    fclose(fp);
}

// retrieve data from "studentsdb.txt" if available
void retrieve()
{
    FILE *fp;
    char sn[31];
    int qz1, qz2, qz3;
    fp = fopen("studentsdb.txt", "r+");

    if (fp == NULL)
    {
        printf("File Error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %d %d %d\n", sn, &qz1, &qz2, &qz3);
            add(sn, qz1, qz2, qz3);
        }
    }
    fclose(fp);
}

void display()
{
    if (isempty())
    {

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
    system("clear");
    printf("Menu\n");
    printf("1.) Insert record\n");
    printf("2.) Update record\n");
    printf("3.) Delete record\n");
    printf("4.) Display\n");
    printf("5.) Exit\n");
    printf("Select(1-5): ");
    scanf("%d", &m);
    return (m);
}

int updatemenu()
{
    int um;
    printf("Menu\n");
    printf("1.) Update Quiz 1\n");
    printf("2.) Update Quiz 2\n");
    printf("3.) Update Quiz 3\n");
    printf("0.) Goto Main Menu\n");
    printf("Select From 1-3 or Press 0: ");
    scanf("%d", &um);
    return (um);
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