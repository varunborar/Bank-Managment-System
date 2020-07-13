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
    string getAddress()
    {
        return address;
    }
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    string getMobileNumber()
    {
        return mobileNumber;
    }
    date getDOB()
    {
        return DOB;
    }
};

class Account : public Person
{

    long accountNumber;
    long accountBalance;
    char password[11];

public:
    long getAccountNumber()
    {
        return accountNumber;
    }
    long getBalance()
    {
        return accountBalance;
    }
    void writeAccountInfo();             //done
    void readAccountInfo();              //done
    void setPassword();                  //done
    void setAccountNumber();             //done
    void createAccount();                //done
    void showAccountInfo();              //done
    void depositBalance(long deposit);   //done
    void withdrawBalance(long withdraw); //done
    void setAccountInfo();               //done
};

void Account ::depositBalance(long deposit)
{
    accountBalance = accountBalance + deposit;
}

void Account ::withdrawBalance(long withdraw)
{
    if (withdraw > accountBalance)
    {
        cout << "\nNot enough balance!";
    }
    else
    {
        accountBalance = accountBalance - withdraw;
    }
}

void writeAccountInfo(Account writeAcc)
{
    fstream sendToFile;
    sendToFile.open("Accounts.dat", ios::app | ios::binary);
    sendToFile.write((char *)&writeAcc, sizeof(writeAcc));
    sendToFile.close();
}

Account readAccountInfo(long accountNumber)
{
    Account acc;
    fstream readFromFile;
    int flag = 0;
    readFromFile.open("Accounts.dat", ios::in | ios::binary);

    if (!readFromFile)
    {
        cout << "\nNo Record Found!";
    }

    while (!readFromFile.eof())
    {
        readFromFile.read((char *)&acc, sizeof(acc));
        if (acc.getAccountNumber() == accountNumber)
        {
            flag = 1;
            return acc;
        }
    }
    if (flag == 0)
    {
        cout << " No Such Account Present";
    }
}

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
    setAccountInfo();
}

void Account ::showAccountInfo()
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

void Account ::setPassword()
{
    cin >> password;
}

void Account ::setAccountNumber()
{
    fstream checkLastAccountNumber;

    checkLastAccountNumber.open("Accounts.dat", ios ::in | ios ::binary);
    if (!checkLastAccountNumber)
    {
        accountNumber = 110000;
    }
    else
    {
        fstream getLastRecord;
        Account last;
        getLastRecord.open("Accounts.dat", ios::in);
        getLastRecord.seekg(-sizeof(last), ios::end);
        getLastRecord.read((char *)&last, sizeof(last));
        long temp = last.getAccountNumber();
        temp++;
        accountNumber = temp;
        getLastRecord.close();
    }
}

void Account ::setAccountInfo()
{
    system("cls");
    gotoxy(0,60);
    cout<<"Account Information";
    gotoxy(5,5);
    cout<<"ENTER A PASSWORD : ";
    gotoxy(5,6);
    cout<<"Enter Intial Deposit Amount : ";
    gotoxy(35,5);
    setPassword();
    gotoxy(35,6);
    int balance;
    cin>> balance;
    depositBalance(balance);

    showAccountInfo();
}
//Main Function

int main()
{

    Account test;
    test.createAccount();
    test.showAccountInfo();

    return 0;
}