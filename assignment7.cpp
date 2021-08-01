// Assingment 7
// Submitted by Ronald T. Tolentino
// TUP / CS203
//Array of structures in C++

/*
Instructions
Modify ArStruct.cpp to use the student records with menu.
    Menu
    Insert
    Update
    Delete
    Display
    Exit
*/

#include <iostream>
#include <fstream>
#include <cmath>

#define MAX 3
using namespace std;

typedef struct student
{
    string name;
    int quiz1, quiz2, quiz3;
} STUDENT;

class studentsStruct
{
private:
    STUDENT A[MAX]; //Array of structure
    int last;
    int locate(string n);
    bool isfull(); //returns true or false
public:
    void init();
    void add(string n, int a, int b, int c);
    void del(string n);
    void update(string n);
    void save();
    void retrieve();
    void display();
};

int menu();
int updatemenu();
float round2(float x);

int main()
{
    studentsStruct ars;
    string nm;
    int a, b, c;

    ars.init();
    ars.retrieve();

    while (1)
    {
        switch (menu())
        {
        case 1:
            system("cls");
            cout << "Insert Mode" << endl;
            cout << "Name: ";
            cin >> nm;
            cout << "Input Quiz 1: ";
            cin >> a;
            cout << "Input Quiz 2: ";
            cin >> b;
            cout << "Input Quiz 3: ";
            cin >> c;
            ars.add(nm, a, b, c);
            break;
        case 2:
            system("cls");
            cout << "Update Mode" << endl;
            cout << "Input Students Name: ";
            cin >> nm;
            ars.update(nm);
            break;
        case 3:
            system("cls");
            cout << "Delete Mode" << endl;
            cout << "Enter Name: ";
            cin >> nm;
            ars.del(nm);
            break;
        case 4:
            ars.display();
            break;
        case 5:
            ars.save();
            exit(0);
        default:
            cout << "1 to 5 only. ";
            system("pause");
        }
    }
    return 0;
}

void studentsStruct::init()
{
    last = -1;
}
void studentsStruct::add(string n, int a, int b, int c)
{
    if (isfull())
    {
        cout << "Array is full." << endl;
        system("pause");
    }
    else
    {
        last++;
        A[last].name.assign(n);
        A[last].quiz1 = a;
        A[last].quiz2 = b;
        A[last].quiz3 = c;
        save();
    }
}
void studentsStruct::del(string n)
{
    int i, p;
    p = locate(n);
    if (p == -1)
    {
        cout << n << " "
             << "not found.\n";
        system("pause");
    }
    else
    {
        for (i = p; i < last; i++)
            A[i] = A[i + 1];
        last--;
        cout << n << "Record deleted." << endl;
        save();
        system("pause");
    }
}

void studentsStruct::update(string n)
{
    int p, ua, ub, uc;
    p = locate(n);
    if (p == -1)
    {
        cout << n << " "
             << "not found." << endl;
        system("pause");
    }
    else
    {
        while (1)
        {
            cout << "Update Mode" << endl;
            cout << "Student : " << A[p].name << endl;
            cout << "Quiz 1 Grade: " << A[p].quiz1 << endl;
            cout << "Quiz 2 Grade: " << A[p].quiz2 << endl;
            cout << "Quiz 3 Grade: " << A[p].quiz3 << endl;

            switch (updatemenu())
            {
            case 1:
                cout << "Quiz 1 Grade: ";
                cin >> ua;
                A[p].quiz1 = ua;
                save();
                break;
            case 2:
                cout << "Quiz 2 Grade: ";
                cin >> ub;
                A[p].quiz2 = ub;
                save();
                break;
            case 3:
                cout << "Quiz 3 Grade: ";
                cin >> uc;
                A[p].quiz3 = uc;
                save();
                break;
            case 4:
                main();
                save();
                break;
            default:
                cout << "Select an option between 1 to 3" << endl;
                cout << "or select 4 to exit the Update Menu: " << endl;
            }
        }
    }
}

int updatemenu()
{
    int um;
    cout << "Update Menu" << endl;
    cout << "1.) Update Quiz 1 Grade" << endl;
    cout << "2.) Update Quiz 2 Grade" << endl;
    cout << "3.) Update Quiz 3 Grade" << endl;
    cout << "4.) Return to the Main Menu" << endl;
    cout << "Select an option between 1 to 3" << endl;
    cout << "or select 4 to exit the Update Menu: ";
    cin >> um;
    return (um);
}

void studentsStruct::display()
{
    int i;
    float ave;
    string remarks;
    system("cls");
    cout << "No.\tNAME\tQUIZ 1\tQUIZ 2\tQUIZ 3\tAVERAGE\tREMARKS\n";
    for (i = 0; i <= last; i++)
    {
        ave = (A[i].quiz1 + A[i].quiz2 + A[i].quiz3) / 3.0;

        remarks = ave >= 75 ? "PASSED" : "FAILED";
        cout << i + 1 << ".)\t" << A[i].name << "\t" << A[i].quiz1 << "\t" << A[i].quiz2 << "\t" << A[i].quiz3 << "\t" << round2(ave) << "\t" << remarks << endl;
    }
    system("pause");
}

int studentsStruct::locate(string n)
{
    for (int i = 0; i <= last; i++)
        if (A[i].name == n)
            return i;
    return -1;
}

bool studentsStruct::isfull()
{
    return (last == MAX - 1);
}

int menu()
{
    int op;
    cout << "Menu" << endl;
    cout << "1.) Insert" << endl;
    cout << "2.) Update" << endl;
    cout << "3.) Delete" << endl;
    cout << "4.) Display" << endl;
    cout << "5.) Exit" << endl;
    cout << "Select(1-5): ";
    cin >> op;
    return (op);
}

void studentsStruct::save()
{
    ofstream stuData;
    stuData.open("studentsdb.txt");

    for (int i = 0; i <= last; i++)
    {
        stuData << A[i].name << " " << A[i].quiz1 << " " << A[i].quiz2 << " " << A[i].quiz3 << endl;
    }
    stuData.close();
}

void studentsStruct::retrieve()
{

    ifstream fp;
    string n;
    int ax, by, cz;

    fp.open("studentsdb.txt");

    if (fp.peek() != std::ifstream::traits_type::eof())
    {
        while (fp >> n >> ax >> by >> cz)
        {
            add(n, ax, by, cz);
        }
    }
    else
    {
        cout << "File is available but its empty" << endl;
    }

    fp.close();
}

float round2(float x)
{
    return trunc(x * 100.0) / 100.0;
}