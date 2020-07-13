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
    //string address;
    unsigned int age;

public:
    void setName()
    {
        getline(cin, name);
    }
    void setMobileNumber()
    {
        getline(std::cin, mobileNumber);
    }
    void setDOB()
    {
        cin >> DOB.day >> DOB.month >> DOB.year;
    }
    // void setAddress()
    // {
    //     getline(cin, address);
    // }
    void setAge()
    {
        cin >> age;
    }
    // string getAddress()
    // {
    //     return address;
    // }
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
    char *getPassword()
    {
        return password;
    }
    // void writeAccountInfo(Account writeAcc);  //done
    // Account readAccountInfo(long accountNum); //done
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

Account readAccountInfo(long accountNum, int flag)
{
    Account acc;
    fstream readFromFile;

    readFromFile.open("Accounts.dat", ios::in | ios::binary);

    if (!readFromFile)
    {
        cout << "\nNo Record Found!";
    }

    while (!readFromFile.eof())
    {
        readFromFile.read((char *)&acc, sizeof(acc));
        if (acc.getAccountNumber() == accountNum)
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
    // cout << "Enter your home address  : ";
    // gotoxy(5, 9);
    cout << "Enter your Date of Birth (DD MM YYYY) : ";
    gotoxy(35, 5);
    setName();
    gotoxy(35, 6);
    setMobileNumber();
    gotoxy(35, 7);
    setAge();
    gotoxy(35, 8);
   //setAddress();
   // gotoxy(45, 9);
    setDOB();
    setAccountInfo();
}

void Account ::showAccountInfo()
{
    system("cls");
    gotoxy(90, 0);
    cout << "Account Information";
    gotoxy(5, 5);
    cout << "Name          : " << getName();
    gotoxy(5, 6);
    cout << "Age           : " << getAge();
    gotoxy(5, 7);
    cout << "Mobile Number : " << getMobileNumber();
    gotoxy(5, 8);
    //cout << "Home address  : " << getAddress();
    //gotoxy(5, 9);
    date dob = getDOB();
    cout << "Date of Birth : " << dob.day << "-" << dob.month << "-" << dob.year;
    gotoxy(5, 15);
    cout << "Bank Account Number : " << getAccountNumber() << endl;
    gotoxy(5, 16);
    cout << "Password : " << getPassword() << endl;
    system("pause");
}

void Account ::setPassword()
{
    cin >> password;
}

void Account ::setAccountNumber()
{
    ifstream checkLastAccountNumber;

    checkLastAccountNumber.open("Accounts.dat", ios ::in);
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
    gotoxy(0, 60);
    cout << "Account Information";
    gotoxy(5, 5);
    cout << "ENTER A PASSWORD : ";
    gotoxy(5, 6);
    cout << "Enter Intial Deposit Amount : ";
    gotoxy(35, 5);
    setPassword();
    gotoxy(35, 6);
    int balance;
    cin >> balance;
    depositBalance(balance);

    showAccountInfo();
}

//Funtion Declaration
void login();
void MainOption(char mainOption);
void MainMenu();
void loginMenu(Account userAccount);

//Main Function

int main()
{
    system("cls");
    // Account test;
    // test.createAccount();
    MainMenu();
    return 0;
}

//Function Definations
void MainMenu()
{
    char mainOption;
    gotoxy(60, 0);
    cout << "Welcome to the Bank!" << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice : ";
    cin >> mainOption;
    MainOption(mainOption);
}

void MainOption(char mainOption)
{
    Account newAccount;
    switch (mainOption)
    {
    case '1':
        system("cls");
        newAccount.createAccount();
        writeAccountInfo(newAccount);
        break;
    case '2':
        system("cls");
        login();
        break;
    case '3':
        system("exit");
        break;
    default:
        cout << "Enter a Valid Choice!";
        break;
    }
}

void login()
{
    Account userAccount;
    long checkAccountNumber;
    int flag = 0;
    char checkPassword[10];
    gotoxy(35, 40);
    cout << "Enter Account Number : ";
    cin >> checkAccountNumber;
    userAccount = readAccountInfo(checkAccountNumber, flag);
    if (flag == 1)
    {
        gotoxy(35, 41);
        cout << "Enter Password : ";
        cin >> checkPassword;
        if (checkPassword == userAccount.getPassword())
        {
            loginMenu(userAccount);
        }
    }
}

void loginMenu(Account userAccount)
{
Start:

    char subMenuOption;
    system("cls");
    gotoxy(0, 4);
    cout << "1. Show Account Information" << endl;
    cout << "2. Check Balance" << endl;
    cout << "3. Deposit Money" << endl;
    cout << "4. Withdraw Money" << endl;
    cout << "Press L to logout" << endl;
    cout << "Enter your Choice";
    cin >> subMenuOption;

    switch (subMenuOption)
    {
    case '1':
        system("cls");
        userAccount.showAccountInfo();
        break;
    case '2':
        system("cls");
        userAccount.getBalance();
        break;
    case '3':
        system("cls");
        int balance;
        cout << "Enter the amount you want to deposit : ";
        cin >> balance;
        userAccount.depositBalance(balance);
        cout << "Final Balance : " << userAccount.getBalance();
        break;
    case '4':
        system("cls");
        int withdraw;
        cout << "Enter the amount you want to withdraw : ";
        cin >> withdraw;
        userAccount.withdrawBalance(withdraw);
        cout << "Final Balance : " << userAccount.getBalance();
        break;
    case 'L':
    case 'l':
        MainMenu();
        break;
    default:
        cout << "\n Enter a Valid Choice";
        goto Start;
    }
}