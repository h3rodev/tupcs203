// Assignment 2
// Submitted by Ronald T. Tolentino
// TUP / CS203

// Instructions
// Modify assignment 1 to use function and local variables.

#include <stdio.h>
#include <stdlib.h>

#define MAX 3

// Declare User-Defined Functions
void getStudentsRec(char students[][31], int q1[], int q2[], int q3[]);
float studentsAve(int q1, int q2, int q3);
void showResults(char stu[][31], int q1[], int q2[], int q3[]);

int main()
{
    // Declare Local Variables
    char students[MAX][31];
    int q1[MAX], q2[MAX], q3[MAX], i;

    getStudentsRec(students, q1, q2, q3);
    showResults(students, q1, q2, q3);
    return 0;
}

// this fuction will get the students Names & Quizzes
void getStudentsRec(char students[][31], int q1[], int q2[], int q3[])
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        printf("Enter Student Name: ");
        scanf("%s", students[i]);

        printf("Enter Quiz 1: ");
        scanf("%d", &q1[i]);

        printf("Enter Quiz 2: ");
        scanf("%d", &q2[i]);

        printf("Enter Quiz 3: ");
        scanf("%d", &q3[i]);
    }
}

// Show and display all the students Names, Quizzes, Average and check for passig remarks
void showResults(char students[][31], int q1[], int q2[], int q3[])
{
    float ave;
    int i;
    system("cls");
    printf("No.  NAME  Q1  Q2  Q3  AVE  REMARKS\n");

    for (i = 0; i < MAX; i++)
    {
        ave = studentsAve(q1[i], q2[i], q3[i]);
        printf("%d.) %s  %d  %d  %d  %6.2f  %s\n", i + 1, students[i], q1[i], q2[i], q3[i], ave, ave >= 75.0 ? "PASSED" : "FAILED");
    }
}

// get students quiz scores and return an average
float studentsAve(int quiz1, int quiz2, int quiz3)
{
    float sAve = (quiz1 + quiz2 + quiz3) / 3.0;
    return (sAve);
}
