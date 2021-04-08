#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include<string.h>

using namespace std;
struct date
{
	int day;
	int month;
	int year;
};
struct list
{
	int number = 0;
	string title;
	string detail;
	date due_date;
	char priority;
	bool done = false;
	bool overdue = false;
};
list task[100];
int no_of_tasks = 0;
SYSTEMTIME a;
int search;
int v_number;
date v_date;
string v_string;
bool found = false;
bool while_loop = false;
void set_done(list task[], int position, int no_of_tasks)
{
	if (position <= no_of_tasks)
	{
		task[position].done = true;
	}
}
void edit(list task[], int t, int no_of_tasks)
{
	if (t < no_of_tasks)
	{
		cin.ignore();
		cout << "Enter Task Number #" << t + 1 << " Title" << endl;
		getline(cin, task[t].title);
		cout << "Enter Task Number #" << t + 1 << " Details" << endl;
		getline(cin, task[t].detail);
		cout << "Enter Task Number #" << t + 1 << " Due Date" << endl;
		cin >> task[t].due_date.day >> task[t].due_date.month >> task[t].due_date.year;
		cout << "Enter Task Number #" << t + 1 << " Priority" << endl;
		cin >> task[t].priority;
		for (int i = 0; i < no_of_tasks; i++)
		{
			cout << "Task Number #" << i + 1 << " Title" << ":" << task[i].title << endl;
			cout << "Task Number #" << i + 1 << " Details" << ":" << task[i].detail << endl;
			cout << "Task Number #" << i + 1 << " Due Date" << ":" << task[i].due_date.day << "/" << task[i].due_date.month << "/" << task[i].due_date.year << endl;
			cout << "Task Number #" << i + 1 << " Priority" << ":" << task[i].priority << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "Task Not Available" << endl;
	}
}
void delete_task(int position, int& no_of_tasks)
{
	if (no_of_tasks == 0)
	{
		cout << "No Tasks To Be Deleted" << endl;
	}
	else if (position < no_of_tasks)
	{
		for (int i = position; i < no_of_tasks; i++)
		{
			list temp = task[i];
			task[i] = task[i + 1];
			task[i + 1] = temp;
		}
		no_of_tasks = no_of_tasks - 1;
		for (int i = 0; i < no_of_tasks; i++)
		{
			cout << "Task Number #" << i + 1 << " Title" << ":" << task[i].title << endl;
			cout << "Task Number #" << i + 1 << " Details" << ":" << task[i].detail << endl;
			cout << "Task Number #" << i + 1 << " Due Date" << ":" << task[i].due_date.day << "/" << task[i].due_date.month << "/" << task[i].due_date.year << endl;
			cout << "Task Number #" << i + 1 << " Priority" << ":" << task[i].priority << endl;
			cout << endl;
		}
	}
	else {
		cout << "Task Not Available" << endl;
	}
}
void display(list task[], int x)
{
	for (int i = 0; i < x; i++)
	{
		cout << "Task Number #" << i + 1 << " Title" << ":" << task[i].title << endl;
		cout << "Task Number #" << i + 1 << " Details" << ":" << task[i].detail << endl;
		cout << "Task Number #" << i + 1 << " Due Date" << ":" << task[i].due_date.day << "/" << task[i].due_date.month << "/" << task[i].due_date.year << endl;
		cout << "Task Number #" << i + 1 << " Priority" << ":" << task[i].priority << endl;
		cout << endl;
	}
}
void show_done(list task[], int x) {
	int z = 0;
	for (int i = 0; i < x; i++)
	{
		if (task[i].done)
		{
			cout << task[i].title << "\t" << task[i].detail << "\t" << task[i].priority << "\t" << task[i].due_date.day << '/' << task[i].due_date.month << '/' << task[i].due_date.year << '\n';
			z++;
			break;
		}
	}
	if (z == 0)
	{
		cout << "No Done Tasks Found" << endl;
	}
}
void overdue(list task[], int no_of_tasks)
{
	SYSTEMTIME a;
	GetLocalTime(&a);
	for (int i = 0; i < no_of_tasks; i++)
	{
		if ((task[i].done != true && task[i].due_date.year < a.wYear) || (task[i].done == false && task[i].due_date.year == a.wYear && task[i].due_date.month < a.wMonth) || (task[i].done == false && task[i].due_date.year == a.wYear && task[i].due_date.month == a.wMonth && task[i].due_date.day < a.wDay))
		{
			task[i].overdue = true;
			cout << "Task Number #" << i + 1 << " Title" << ":" << task[i].title << endl;
			cout << "Task Number #" << i + 1 << " Details" << ":" << task[i].detail << endl;
			cout << "Task Number #" << i + 1 << " Due Date" << ":" << task[i].due_date.day << "/" << task[i].due_date.month << "/" << task[i].due_date.year << endl;
			cout << "Task Number #" << i + 1 << " Priority" << ":" << task[i].priority << endl;
			cout << endl;
		}
	}
}
void date_today(SYSTEMTIME)
{
	GetLocalTime(&a);
	int z = 0;
	for (int i = 0; i < no_of_tasks; i++) {

		if (a.wDay == task[i].due_date.day && a.wMonth == task[i].due_date.month && a.wYear == task[i].due_date.year) {
			cout << task[i].title << "\t" << task[i].detail << "\t" << task[i].priority << "\t" << task[i].due_date.day << '/' << task[i].due_date.month << '/' << task[i].due_date.year << '\n';
			z++;
			found = true;
			break;
		}
	}
	if (z == 0)
	{
		cout << "No Task Should Be Done Today" << endl;
	}
}
void search_string(string) {
	cout << "Enter title to serach:\n";
	getline(cin, v_string);
	for (int i = 0; i < no_of_tasks; i++) {
		if (task[i].title.find(v_string) != std::string::npos) {
			cout << task[i].title << "\t" << task[i].detail << "\t" << task[i].priority << "\t" << task[i].due_date.day << '/' << task[i].due_date.month << '/' << task[i].due_date.year << '\n';
			found = true;
		}
	}
	if (found == false) {
		cout << "Not Found\n";
	}
}
void search_number(int) {
	cout << "enter number to search :\n";
	cin >> v_number;
	for (int i = 0; i < no_of_tasks; i++) {

		if (v_number == task[i].number) {
			cout << task[i].title << "\t" << task[i].detail << "\t" << task[i].priority << "\t" << task[i].due_date.day << '/' << task[i].due_date.month << '/' << task[i].due_date.year << '\n';
			found = true;
		}
	}
	if (found == false) {
		cout << "Not Found\n";
	}
}
void search_date(date) {
	cout << "enter date to search :\n";
	cin >> v_date.day >> v_date.month >> v_date.year;

	for (int i = 0; i < no_of_tasks; i++) {

		if (v_date.day == task[i].due_date.day && v_date.month == task[i].due_date.month && v_date.year == task[i].due_date.year) {
			cout << task[i].title << "\t" << task[i].detail << "\t" << task[i].priority << "\t" << task[i].due_date.day << '/' << task[i].due_date.month << '/' << task[i].due_date.year << '\n';
			found = true;
		}
	}
	if (found == false) {
		cout << "Not Found\n";
	}
}
int retrieve_data(list task[], int no_of_tasks)
{
	ifstream Tasks("No_of_Tasks.txt");
	Tasks >> no_of_tasks;
	ifstream Task("Lists.txt");
	int i = 0;
	for (int i = 0; i < no_of_tasks; i++)
	{
		getline(Task, task[i].title);
		getline(Task, task[i].detail);
		Task >> task[i].due_date.day >> task[i].due_date.month >> task[i].due_date.year >> task[i].number >> task[i].priority >> task[i].done >> task[i].overdue;
	}
	return no_of_tasks;
}
void save_data(list task[], int no_of_tasks)
{
	ofstream Tasks("No_of_Tasks.txt");
	Tasks << no_of_tasks;
	ofstream Task("Lists.txt");
	for (int i = 0; i < no_of_tasks; i++)
	{
		Task << task[i].title << endl;
		Task << task[i].detail << endl;
		Task << task[i].due_date.day << "  " << task[i].due_date.month << "  " << task[i].due_date.year << "  " << task[i].number << "  " << task[i].priority << "  " << task[i].done << "  " << task[i].overdue;
		cout << endl;
	}
}
int main()
{
	ifstream Account("Info.txt");
	string username;
	string password;
	getline(Account, username);
	getline(Account, password);
	cout << "Enter Username: ";
	string username_entered;
	getline(cin, username_entered);
	cout << "Enter Password: ";
	string password_entered;
	getline(cin, password_entered);
	if ((username_entered.compare(username) == 0) && (password_entered.compare(password) == 0))
	{
		no_of_tasks = retrieve_data(task, no_of_tasks);
		int loop = 1;
		for (int counter = 0; counter < loop;)
		{
			cout << "1.Add New Task" << endl;
			cout << "2.Mark Task As Done" << endl;
			cout << "3.Edit Task" << endl;
			cout << "4.Delete Task" << endl;
			cout << "5.Display All Tasks" << endl;
			cout << "6.Display All Done Tasks" << endl;
			cout << "7.Display All Overdue Tasks" << endl;
			cout << "8.Display Tasks Need To Be Done Today" << endl;
			cout << "9.Search For Tasks" << endl;
			cout << "10.Change Account Details" << endl;
			int operation;
			cout << "Enter number of operation you want : " << endl;
			cin >> operation;
			cin.ignore();
			switch (operation)
			{
			case 1: {
				no_of_tasks++;
				for (int i = (no_of_tasks - 1); i < no_of_tasks;)
				{
					i = no_of_tasks - 1;
					task[i].number = i + 1;
					char add_task = 'N';
					cout << "Enter Task Number #" << i + 1 << " Title" << endl;
					getline(cin, task[i].title);
					cout << "Enter Task Number #" << i + 1 << " Details" << endl;
					getline(cin, task[i].detail);
					cout << "Enter Task Number #" << i + 1 << " Due Date" << endl;
					cin >> task[i].due_date.day >> task[i].due_date.month >> task[i].due_date.year;
					if (task[i].due_date.day > 31 || task[i].due_date.day < 1)
					{
						cout << "Day Incorrect" << endl;
						cout << "Enter Task Number #" << i + 1 << " Due Date" << endl;
						cin >> task[i].due_date.day >> task[i].due_date.month >> task[i].due_date.year;
					}
					if (task[i].due_date.month < 1 || task[i].due_date.month>12)
					{
						cout << "Month Incorrect" << endl;
						cout << "Enter Task Number #" << i + 1 << " Due Date" << endl;
						cin >> task[i].due_date.day >> task[i].due_date.month >> task[i].due_date.year;
					}

					cout << "Enter Task Number #" << i + 1 << " Priority" << endl;
					cin >> task[i].priority;
					cout << "Do you want to add new task ? Enter (Y/N)" << endl;
					cin >> add_task;
					cin.ignore();
					if (add_task == 'Y' || add_task == 'y')
					{
						no_of_tasks++;
					}
					else
					{
						break;
					}
				}
				break;
			}
			case 2: {
				cout << "Which task should be marked done ?" << endl;
				int x;
				cin >> x;
				set_done(task, (x - 1), no_of_tasks);
				if (x <= no_of_tasks)
				{
					cout << "Task Number #" << x << " Done" << endl;
				}
				else {
					cout << "Task Not Found" << endl;
				}
				break;
			}
			case 3: {
				cout << "Which tasks would you like to change?" << endl;
				int t;
				cin >> t;
				t--;
				edit(task, t, no_of_tasks);
				break;
			}
			case 4: {
				cout << "which task would you like to delete?";
				int position;
				cin >> position;
				position--;
				delete_task(position, no_of_tasks);
				break;
			}
			case 5: {
				cout << "All Tasks" << endl;
				display(task, no_of_tasks);
				break;
			}
			case 6: {
				cout << "Done Tasks" << endl;
				show_done(task, no_of_tasks);
				break;
			}
			case 7: {
				cout << "Tasks Overdue" << endl;
				overdue(task, no_of_tasks);
				break;
			}
			case 8: {
				cout << "Tasks That Should Be Done Today" << endl;
				date_today(a);
				break;
			}
			case 9: {
				cout << "enter (1) to serach by title, (2) by date or (3) by number :"; cin >> search;
				cin.ignore();

				switch (search) {
				case 1:
					search_string(v_string);
					break;
				case 2:
					search_date(v_date);
					break;
				case 3:
					search_number(v_number);
					break;
				default:
					cout << "invalid entry:\n";
					break;
				}
				break;
			}
			case 10: {
				system("CLS");
				cout << "1.Account Username" << endl;
				cout << "2.Account Password" << endl;
				cout << "3.Account Username And Password" << endl;
				int account_operation;
				cout << "Enter number of operation you want : " << endl;
				cin >> account_operation;
				cin.ignore();
				switch (account_operation)
				{
				case 1: {
					cout << "Enter New Username :" << endl;
					getline(cin, username);
					ofstream Account("Info.txt");
					Account << username << endl;
					Account << password << endl;
					break;
				}
				case 2: {
					cout << "Enter New Password :" << endl;
					getline(cin, password);
					ofstream Account("Info.txt");
					Account << username << endl;
					Account << password << endl;
					break;
				}
				case 3: {
					cout << "Enter New Username :" << endl;
					getline(cin, username);
					cout << "Enter New Password :" << endl;
					getline(cin, password);
					ofstream Account("Info.txt");
					Account << username << endl;
					Account << password << endl;
					break;
				}
				default: {
					cout << "Invalid Operation:\n";
					break;
				}
				}
				break;
			}
			default: {
				cout << "Invalid Operation:\n";
				break;
			}
			}
			cout << "Do you want to do another operation ? Enter (Y/N)" << endl;
			char Another_Operation = 'N';
			cin >> Another_Operation;
			if (Another_Operation == 'Y' || Another_Operation == 'y')
			{
				loop++;
				system("CLS");
			}
			else {
				break;
			}
		}
		save_data(task, no_of_tasks);
		system("pause");
		return 0;
	}
	else
	{
		cout << "Username Or Password Incorrect." << endl;
		system("pause");
		return 0;
	}
}