// Assingment 4
// Submitted by Ronald T. Tolentino
// TUP / CS203

/* Instructions
Modify Quiz1 to use Array of Structures instead of Parallel Arrays.
Hint:
typedef struct record{
      char name[31];
      int q1,q2,q3;
} REC;
REC stude[MAX];
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
Student studentRecord[MAX];

// Global Variables
// char student[MAX][31];
// int quiz1[MAX], quiz2[MAX], quiz3[MAX];
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
            system("cls");
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
    last = -1;
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
        last = last + 1;
        strcpy(studentRecord[last].name, sn);
        studentRecord[last].quiz1 = qa;
        studentRecord[last].quiz2 = qb;
        studentRecord[last].quiz3 = qc;
        system("cls");
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
                printf("Student: %s\n", studentRecord[p].name);
                printf("QUIZ 1: %d\n", studentRecord[p].quiz1);
                printf("QUIZ 2: %d\n", studentRecord[p].quiz2);
                printf("QUIZ 3: %d\n", studentRecord[p].quiz3);
                switch (updatemenu())
                {
                case 1:
                    printf("QUIZ 1:");
                    scanf("%d", &uq1);
                    studentRecord[p].quiz1 = uq1;
                    break;
                case 2:
                    printf("QUIZ 2:");
                    scanf("%d", &uq2);
                    studentRecord[p].quiz2 = uq2;
                    break;
                case 3:
                    printf("QUIZ 3:");
                    scanf("%d", &uq3);
                    studentRecord[p].quiz3 = uq3;
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
            for (i = p; i < last; i++)
            {
                strcpy(studentRecord[i].name, studentRecord[i + 1].name);
                studentRecord[i].quiz1 = studentRecord[i + 1].quiz1;
                studentRecord[i].quiz2 = studentRecord[i + 1].quiz2;
                studentRecord[i].quiz3 = studentRecord[i + 1].quiz3;
            }
            printf("DELETE MODE\n");
            printf("%s is now deleted..\n", sn);
            last--;
        }
    }
}

// Search records using the students name.
int search(char sn[31])
{
    int i;
    for (i = 0; i <= last; i++)
        if (strcmp(studentRecord[i].name, sn) == 0)
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
            fprintf(fp, "%s %d %d %d\n", studentRecord[i].name, studentRecord[i].quiz1, studentRecord[i].quiz2, studentRecord[i].quiz3);
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
        system("cls");
        printf("DISPLAY MODE\n");
        printf("Array is empty...\n");
        printf("There is nothing to display...\n");
        printf("Please Select Other Menu Option...\n");
    }
    else
    {
        int i;
        float ave;
        system("cls");
        printf("DISPLAY MODE\n");
        printf("No.\tNAME\tQuiz 1\tQuiz 2\tQuiz 3\tAverage\tRemarks\n");
        for (i = 0; i <= last; i++)
        {
            ave = getAverage(studentRecord[i].quiz1, studentRecord[i].quiz2, studentRecord[i].quiz3);
            printf("%d.)\t%s\t%d\t%d\t%d\t%6.2f\t%s\n", i + 1, studentRecord[i].name, studentRecord[i].quiz1, studentRecord[i].quiz2, studentRecord[i].quiz3, ave, ave >= 75 ? "Passed" : "Failed");
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
    return (last == MAX - 1);
}

int isempty()
{
    if (last == -1)
        return 1;
    else
        return 0;
}