// Assingment 5
// Submitted by Ronald T. Tolentino
// TUP / CS203

/* Instructions
Modify quiz111.c to use List operations with the following additional requirements:
Modify the insert function so that it will not allow replicate names/records.
Modify insert function to insert the element​/record on its proper position in the file in ascending order.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 3

typedef struct Student
{
    char name[31];
    int quiz1, quiz2, quiz3;
} Student;

typedef struct list
{
    Student studentRecord[MAX];
    int last;
} LIST;
LIST L; //L structure is global

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
    system("cls");
    while (1)
    {
        switch (menu())
        {
        case 1:
            if (!isfull())
            {
                printf("Add Student Mode\n");
                printf("Enter Name: ");
                scanf("%s", sn);

                // check if name for duplicate logic
                if (search(sn) == -1)
                {
                    printf("Enter QUIZ 1: ");
                    scanf("%d", &qa);
                    printf("Enter QUIZ 2: ");
                    scanf("%d", &qb);
                    printf("Enter QUIZ 3: ");
                    scanf("%d", &qc);
                    add(sn, qa, qb, qc);
                }
                else
                {
                    system("cls");
                    printf("%s already exist. Please enter a different name\n\n", sn);
                }
            }
            else
            {
                system("cls");
                printf("Array is Full. Please delete other records or choose other menu.\n\n");
            }
            break;
        case 2:
            system("cls");
            printf("UPDATE MODE\n");
            printf("Enter Student Name: ");
            scanf("%s", sn);
            update(sn);
            break;
        case 3:
            system("cls");
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
    L.last = -1;
}

// Add new Student Name and Quizes.
void add(char sn[31], int qa, int qb, int qc)
{
    if (isfull())
    {
        system("cls");
        printf("Add Student Mode\n");
        printf("Array Is Full!.\n");
        printf("Please Select Other Menu Option.\n");
    }
    else
    {
        L.last++;
        strcpy(L.studentRecord[L.last].name, sn);
        L.studentRecord[L.last].quiz1 = qa;
        L.studentRecord[L.last].quiz2 = qb;
        L.studentRecord[L.last].quiz3 = qc;

        save();
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
    }
    else
    {
        p = search(sn);
        if (p == -1)
        {
            printf("UPDATE MODE\n");
            printf("%s cannot be found.\n", sn);
            printf("Please try again.\n");
        }
        else
        {

            while (1)
            {
                system("cls");
                printf("UPDATE MODE\n");
                printf("Student: %s\n", L.studentRecord[p].name);
                printf("QUIZ 1: %d\n", L.studentRecord[p].quiz1);
                printf("QUIZ 2: %d\n", L.studentRecord[p].quiz2);
                printf("QUIZ 3: %d\n", L.studentRecord[p].quiz3);
                switch (updatemenu())
                {
                case 1:
                    printf("QUIZ 1:");
                    scanf("%d", &uq1);
                    L.studentRecord[p].quiz1 = uq1;
                    break;
                case 2:
                    printf("QUIZ 2:");
                    scanf("%d", &uq2);
                    L.studentRecord[p].quiz2 = uq2;
                    break;
                case 3:
                    printf("QUIZ 3:");
                    scanf("%d", &uq3);
                    L.studentRecord[p].quiz3 = uq3;
                    break;
                case 0:
                    // Call the save function to save all the updates before returning to main menu
                    // To make sure all data are up to date.
                    save();
                    main();

                    break;
                default:
                    printf("1 to 3 or 0 to exit update menu.\n");
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
    }
    else
    {
        p = search(sn);
        if (p == -1)
        {
            printf("DELETE MODE\n");
            printf("%s cannot be found.\n", sn);
            printf("Please try again.\n");
        }
        else
        {
            for (i = p; i < L.last; i++)
            {
                strcpy(L.studentRecord[i].name, L.studentRecord[i + 1].name);
                L.studentRecord[i].quiz1 = L.studentRecord[i + 1].quiz1;
                L.studentRecord[i].quiz2 = L.studentRecord[i + 1].quiz2;
                L.studentRecord[i].quiz3 = L.studentRecord[i + 1].quiz3;
            }
            printf("DELETE MODE\n");
            printf("%s is now deleted..\n", sn);
            L.last--;
        }
    }
}

// Search records using the students name.
int search(char sn[31])
{
    int i;
    for (i = 0; i <= L.last; i++)
        if (strcmp(L.studentRecord[i].name, sn) == 0)
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
        for (i = 0; i <= L.last; i++)
            fprintf(fp, "%s %d %d %d\n", L.studentRecord[i].name, L.studentRecord[i].quiz1, L.studentRecord[i].quiz2, L.studentRecord[i].quiz3);
    }

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
        system("cls");
        printf("DISPLAY MODE\n");
        printf("Array is empty...\n");
        printf("There is nothing to display...\n");
        printf("Please Select Other Menu Option...\n");
    }
    else
    {

        int i, j, qtemp1, qtemp2, qtemp3;
        float ave;
        char temp[31];

        system("cls");

        printf("DISPLAY MODE\n");
        printf("No.\tNAME\tQuiz 1\tQuiz 2\tQuiz 3\tAverage\tRemarks\n");

        // sorting logic
        for (i = 0; i <= L.last; i++)
        {
            for (j = i + 1; j <= L.last; j++)
            {
                if (strcmp(L.studentRecord[i].name, L.studentRecord[j].name) > 0)
                {
                    strcpy(temp, L.studentRecord[i].name);
                    strcpy(L.studentRecord[i].name, L.studentRecord[j].name);
                    strcpy(L.studentRecord[j].name, temp);

                    qtemp1 = L.studentRecord[i].quiz1;
                    L.studentRecord[i].quiz1 = L.studentRecord[j].quiz1;
                    L.studentRecord[j].quiz1 = qtemp1;

                    qtemp2 = L.studentRecord[i].quiz2;
                    L.studentRecord[i].quiz2 = L.studentRecord[j].quiz2;
                    L.studentRecord[j].quiz2 = qtemp2;

                    qtemp3 = L.studentRecord[i].quiz2;
                    L.studentRecord[i].quiz2 = L.studentRecord[j].quiz2;
                    L.studentRecord[j].quiz2 = qtemp3;
                }
            }
            ave = getAverage(L.studentRecord[i].quiz1, L.studentRecord[i].quiz2, L.studentRecord[i].quiz3);
            printf("%d.)\t%s\t%d\t%d\t%d\t%6.2f\t%s\n", i + 1, L.studentRecord[i].name, L.studentRecord[i].quiz1, L.studentRecord[i].quiz2, L.studentRecord[i].quiz3, ave, ave >= 75 ? "Passed" : "Failed");
        }
    }
}

int menu()
{
    int m;

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
    return (L.last == MAX - 1);
}

int isempty()
{
    if (L.last == -1)
        return 1;
    else
        return 0;
}