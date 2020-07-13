#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;
//Essential Functions
void gotoxy(short col, short row)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {col, row};
    SetConsoleCursorPosition(hStdOut, position);
}

//Structures
struct date
{
    int day;
    int month;
    int year;
};

//CLASSES

class Person
{
    string name;
    string mobileNumber;
    date DOB;
    string address;
    unsigned int age;

public:
    void setName()
    {
        getline(cin, name);
    }
    void setMobileNumber()
    {
        getline(cin, mobileNumber);
    }
    void setDOB()
    {
        cin >> DOB.day >> DOB.month >> DOB.year;
    }
    void setAddress()
    {
        getline(cin, address);
    }
    void setAge()
    {
        cin >> age;
    }
    void getAddress()
    {
        cout << address;
    }
    void getName()
    {
        cout << name;
    }
    void getAge()
    {
        cout << age;
    }
    void getMobileNumber()
    {
        cout << mobileNumber;
    }
    void getDOB()
    {
        cout << DOB.day << " " << DOB.month << " " << DOB.year;
    }
};

class Account : public Person
{

    long accountNumber;
    long accountBalance;
    char password[12];

public:
    void createAccount();
    void showAccountInfo();
    void depositBalance();
    void withdrawBalance();
    void checkBalance();
};

void Account ::createAccount()
{
    system("cls");
    gotoxy(90, 0);
    cout << "Create Account";
    gotoxy(5, 5);
    cout << "Enter your Name          : ";
    gotoxy(5, 6);
    cout << "Enter your mobile number : ";
    gotoxy(5, 7);
    cout << "Enter your age           : ";
    gotoxy(5, 8);
    cout << "Enter your home address  : ";
    gotoxy(5, 9);
    cout << "Enter your Date of Birth (DD MM YYYY) : ";
    gotoxy(35, 5);
    setName();
    gotoxy(35, 6);
    setMobileNumber();
    gotoxy(35, 7);
    setAge();
    gotoxy(35, 8);
    setAddress();
    gotoxy(45, 9);
    setDOB();
}

void Account::showAccountInfo()
{
    system("cls");
    gotoxy(90, 0);
    cout << "Account Information";
    gotoxy(5, 5);
    cout << "Name          : ";
    getName();
    gotoxy(5, 6);
    cout << "Age           : ";
    getAge();
    gotoxy(5, 7);
    cout << "Mobile Number : ";
    getMobileNumber();
    gotoxy(5, 8);
    cout << "Home address  : ";
    getAddress();
    gotoxy(5, 9);
    cout << "Date of Birth : ";
    getDOB();
}

//Main Function

int main()
{

    Account test;
    test.createAccount();
    test.showAccountInfo();

    return 0;
}