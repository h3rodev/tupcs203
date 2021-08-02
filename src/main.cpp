// Final Exam
// Submitted by Ronald T. Tolentino
// TUP / CS203
// Link List Pointer Implementation in C++

/*
Write the Link List (pointer version) of your last assigment with file saving ang retrieving.
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

using namespace std;

typedef struct student
{
	string name;
	int quiz1, quiz2, quiz3;
	struct student *nxt;
} STUDENT;

class studentsStruct
{
private:
	STUDENT *S; //Header of the Student List
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
float round2(float x); // function to round the average and limit to 2 decimal points

int main()
{
	studentsStruct ars;
	string nm;
	int a, b, c;

	ars.init();		// Initialize the S Header of the Student List
	ars.retrieve(); // Check if the "studentsdb.txt" is available and load the data as needed

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
	S = NULL;
}

void studentsStruct::add(string n, int a, int b, int c)
{
	STUDENT *p, *q, *temp;
	p = q = S;
	temp = new STUDENT;
	temp->name = n;
	temp->quiz1 = a;
	temp->quiz2 = b;
	temp->quiz3 = c;

	while (p != NULL)
	{
		q = p;
		p = p->nxt;
	}
	if (p == S)
	{
		S = temp;
	}
	else
	{
		q->nxt = temp;
		temp->nxt = p;
	}
}

void studentsStruct::del(string n)
{
	STUDENT *p, *q;
	p = q = S;
	while (p != NULL && p->name != n)
	{
		q = p;
		p = p->nxt;
	}
	if (p == NULL)
	{
		cout << n << (" is not found.") << endl;
		system("pause");
	}
	else
	{
		if (p == S)
		{
			S = S->nxt;
		}
		else
		{
			q->nxt = p->nxt;
			delete (p);
			cout << n << (" is deleted from students records") << endl;
		}
	}
}

void studentsStruct::update(string n)
{
	STUDENT *p, *q;
	p = q = S;
	int ua, ub, uc;

	while (p != NULL && p->name != n)
	{
		q = p;
		p = p->nxt;
	}
	if (p == NULL)
	{
		cout << ("Not Found.") << endl;
		system("pause");
	}
	else
	{
		while (1)
		{
			cout << "Update Mode" << endl;
			cout << "Student : " << p->name << endl;
			cout << "Quiz 1 Grade: " << p->quiz1 << endl;
			cout << "Quiz 2 Grade: " << p->quiz2 << endl;
			cout << "Quiz 3 Grade: " << p->quiz3 << endl;

			switch (updatemenu())
			{
			case 1:
				cout << "Quiz 1 Grade: ";
				cin >> ua;
				p->quiz1 = ua;
				save();
				break;
			case 2:
				cout << "Quiz 2 Grade: ";
				cin >> ub;
				p->quiz2 = ub;
				save();
				break;
			case 3:
				cout << "Quiz 3 Grade: ";
				cin >> uc;
				p->quiz3 = uc;
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
	STUDENT *p;
	int i = 1;
	p = S;
	float ave;
	string remarks;
	system("cls");
	cout << "No.\tNAME\tQUIZ 1\tQUIZ 2\tQUIZ 3\tAVERAGE\tREMARKS\n";

	while (p != NULL)
	{
		ave = (p->quiz1 + p->quiz2 + p->quiz3) / 3.0;
		remarks = ave >= 75 ? "PASSED" : "FAILED";
		cout << i++ << ".)\t" << p->name << "\t" << p->quiz1 << "\t" << p->quiz2 << "\t" << p->quiz3 << "\t" << round2(ave) << "\t" << remarks << endl;
		p = p->nxt;
	}
	system("pause");
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

// Save the student data to "studentsdb.txt" if available and create a file if needed
void studentsStruct::save()
{
	STUDENT *p;
	p = S;
	ofstream stuData;
	stuData.open("studentsdb.txt");

	while (p != NULL)
	{
		stuData << p->name << " " << p->quiz1 << " " << p->quiz2 << " " << p->quiz3 << endl;
		p = p->nxt;
	}

	stuData.close();
}

// Check if the "studentsdb.txt" is available and load the data as needed
void studentsStruct::retrieve()
{
	ifstream fp;
	string n;
	int ax, by, cz;

	fp.open("studentsdb.txt");

	while (fp >> n >> ax >> by >> cz)
	{
		add(n, ax, by, cz);
	}

	fp.close();
}

// function to round the average and limit to 2 decimal points
float round2(float x)
{
	return trunc(x * 100.0) / 100.0;
}