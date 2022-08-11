#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
using namespace std;

//array of structure
typedef struct
{
	char ID[8];
	char name[31];
	char pin[10];
	double bal;
}INFORMATION;

//global variable
char idin[8];
char namein[31];
char pinin[8];
double balin;

//Function Prototype
void Login(INFORMATION cus[], int row);
void searchbyID(INFORMATION cus[], int row);
void Welcome();
void Menu(INFORMATION cus[], int row);
void Check();
void Reload();
void Payment(INFORMATION cus[], int row);

//main function
int main()
{
	ifstream in("info.txt");

	if (!in)
	{
		cerr << "Error loading customer information!\n";
		exit(100);
	}

	else
	{
		cout << "Customer information downloaded!" << endl;
		INFORMATION list[50];
		int index = 0;
		//get the number of customer, counter

		string FullName; //To store string and convert to char
		while (!in.eof())
		{
			//get ID
			in >> list[index].ID;
			getline(in, FullName, '\t');
			strcpy_s(list[index].name, FullName.c_str());
			in >> list[index].pin;
			in >> list[index].bal;

			index++;
		}

		in.close();
		Login(list, index);
	}
}

//searchbyID

void searchbyID(INFORMATION cus[], int row)
{
	int i = 0;
	int count = 0;
	char getid[8];
	char getpin[8];
	cout << "ID : ";
	cin.getline(getid, 8);
	for (int i = 0; i < row; i++)
	{
		if (strcmp(cus[i].ID, getid) == 0)
		{
			strcpy_s(idin, cus[i].ID);
			strcpy_s(namein, cus[i].name);
			strcpy_s(pinin, cus[i].pin);
			balin = cus[i].bal;
			count++;
		}
	}

	if (count <= 0)
	{
		cout << "\n=====================================================================================\n";
		cout << "\nThe ID that you've entered doesn't match any account. Please re-enter the ID." << endl;
		cout << "\n=====================================================================================\n";
		searchbyID(cus, row);
	}

	else
	{
		cout << "PIN : ";
		cin.getline(getpin, 8);
		if (strcmp(pinin, getpin) == 0)
		{
			system("cls");
			cout << "\n=====================================================================================\n";
			cout << "\nID and PIN number matched! Login completed!" << endl;
			cout << "\n=====================================================================================\n";
			Menu(cus, row);
		}
		else
		{
			cout << "\n=====================================================================================\n";
			cout << "\nThe PIN number you entered is invalid! Please re-enter ID and PIN." << endl;
			cout << "\n=====================================================================================\n";
			searchbyID(cus, row);
		}
	}
}

void Login(INFORMATION cus[], int row)
{
	cout << "======================================================" << endl;
	cout << "Thank you for using EasyPay!" << endl;
	cout << "Please Login to continue." << endl;
	cout << "======================================================" << endl;
	cout << "\nYou're require to enter your ID and PIN to logon.\n" << endl;
	cout << "======================================================" << endl;
	searchbyID(cus, row);
}

void Welcome()
{
	cout << endl;
	cout << "=======================================================================" << endl;
	cout << "Good day " << namein << "!" << endl;
	cout << "=======================================================================" << endl;
}

void Menu(INFORMATION cus[], int row)
{
	Welcome();
	int choices;
	do
	{
		cout << "Would you like to :" << endl;
		cout << "1. Check your information." << endl;
		cout << "2. Reload balance." << endl;
		cout << "3. Payment." << endl;
		cout << "4. Logout and Exit." << endl;
		cout << "=======================================================================" << endl;
		cout << "Enter the number that you would want to do." << endl;
		cin >> choices;
		cin.ignore(1000, '\n');

		switch (choices)
		{
		case 1: Check();
			break;
		case 2: Reload();
			break;
		case 3: Payment(cus, row);
			break;
		case 4: break;
		default: cout << "Invalid command!\n";
		}
	} while (choices != 4);
	return;
}

void Check()
{
	system("cls");
	cout << "=======================================================================" << endl;
	cout << "Hello " << namein << " !" << endl;
	cout << "=======================================================================" << endl;
	cout << "Details" << endl;
	cout << left << setw(12) << "ID : " << left << idin << endl;
	cout << left << setw(12) << "Balance : " << left << showpoint << balin << endl;
	cout << "=======================================================================" << endl;
	return;
}

void Reload()
{
	system("cls");
	double amount;
	cout << "=======================================================================" << endl;
	cout << "Your current balance is : " << left << balin << endl;
	cout << "=======================================================================" << endl;
	cout << "How much would you like to reload?" << endl;
	cout << "Amount to reload : ";
	cin >> amount;
	if (amount <= 0)
	{
		cout << "Only positive number is accepted.\n";
	}
	else
	{
		int answer;
		cout << "=======================================================================" << endl;
		cout << "Are you sure you want to reload : " << amount << " ?" << endl;
		cout << "If Yes, reply 1.\nIf No, reply 2." << endl;
		cout << "=======================================================================" << endl;
		cin >> answer;

		if (answer == 1) {
			balin = balin + amount;
			system("cls");
			cout << "=======================================================================" << endl;
			cout << "Reload successful!" << endl;
			cout << "Your current amount is : " << balin << endl;
			cout << "=======================================================================" << endl;
		}
		else if (answer == 2)
		{
			system("cls");
			cout << "=======================================================================" << endl;
			cout << "Reload cancel!" << endl;
			cout << "Your current amount is : " << balin << endl;
			cout << "=======================================================================" << endl;
		}
		else
		{
			system("cls");
			cout << "=======================================================================" << endl;
			cout << "Invalid choices!" << endl;
			cout << "=======================================================================" << endl;
			return;
		}
	}
	return;
}

void Payment(INFORMATION cus[], int row)
{
	system("cls");
	int amount;
	cout << "=======================================================================" << endl;
	cout << "Proceeding with Payment." << endl;
	cout << "=======================================================================" << endl;
	cout << "Your currecnt balance is : " << balin << endl;
	cout << "How much would you like to pay?" << endl;
	cout << "Amount : ";
	cin >> amount;
	if (amount > balin)
	{
		int answer;
		cout << "=======================================================================" << endl;
		cout << "You don't have enough balance to pay that amount..." << endl;
		cout << "Would you like to reload?" << endl;
		cout << "1. Yes." << endl;
		cout << "2. No." << endl;
		cout << "=======================================================================" << endl;
		cin >> answer;
		if (answer == 1)
		{
			Reload();
		}
		else if (answer == 2)
		{
			system("cls");
			Menu(cus, row);
		}
		else
		{
			system("cls");
			cout << "Invalid command!" << endl;
			return;
		}
	}
	else if (amount <= -1)
	{
		cout << "=======================================================================" << endl;
		cout << "Please enter positive number!" << endl;
		cout << "=======================================================================" << endl;
		return;
	}
	else if (amount == 0)
	{
		cout << "=======================================================================" << endl;
		cout << "0 Detected. Payment Canceled." << endl;
		cout << "=======================================================================" << endl;
	}
	else
	{
		int i;
		cout << "=======================================================================" << endl;
		cout << "You are paying " << amount << "." << endl;
		cout << "Are you sure?" << endl;
		cout << "1. Yes." << endl;
		cout << "2. No." << endl;
		cout << "=======================================================================" << endl;
		cin >> i;
		switch (i) {
		case 1:
		{
			balin = balin - amount;
			cout << "=======================================================================" << endl;
			cout << "You have paid " << amount << "." << endl;
			cout << "Your current balance is : " << balin << endl;
			cout << "=======================================================================" << endl;
			Menu(cus, row);
		}
		case 2:
		{
			cout << "=======================================================================" << endl;
			cout << "Payment canceled." << endl;
			cout << "Your current balance is : " << balin << endl;
			cout << "=======================================================================" << endl;
			Menu(cus, row);
		}
		default:
		{
			cout << "=======================================================================" << endl;
			cout << "Invalid command!" << endl;
			cout << "=======================================================================" << endl;
		}
		}
	}
}