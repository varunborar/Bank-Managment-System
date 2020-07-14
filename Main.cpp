#include <iostream>
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
    char name[25];
    char mobileNumber[11];
    date DOB;
    unsigned int age;

public:
    void setName(char *nm)
    {
        strcpy(name, nm);
    }
    void setMobileNumber(char *mob)
    {
        strcpy(mobileNumber, mob);
    }
    void setDOB(date dob)
    {
        DOB = dob;
    }
    void setAge(int Age)
    {
        age = Age;
    }
    char *getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    char *getMobileNumber()
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

Account readAccountInfo(long accountNum, int *flag)
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
            *flag = 1;
            return acc;
        }
    }
    if (*flag == 0)
    {
        cout << " No Such Account Present";
    }
    return acc;
}

void Account ::createAccount()
{
    char name[25], mobileNumber[12];
    int age;
    date dob;
    system("cls");

    cout << "\t\t\t\t\t\tCreate Account";

    cout << "\nEnter your Name          : ";
    cin.getline(name, 24);
    setName(name);

    cout << "\nEnter your mobile number : ";
    cin.getline(mobileNumber, 11);
    setMobileNumber(mobileNumber);

    cout << "\nEnter your age           : ";
    cin >> age;
    setAge(age);

    cout << "\nEnter your Date of Birth (DD MM YYYY) : ";
    cin >> dob.day >> dob.month >> dob.year;
    setDOB(dob);

    setAccountInfo();
}

void Account ::showAccountInfo()
{

    system("cls");
    
    cout << "\t\t\t\t\t\tAccount Information";
    
    cout << "\nName          : " << getName();
    
    cout << "\nAge           : " << getAge();
   
    cout << "\nMobile Number : " << getMobileNumber();
    
    date dob = getDOB();
    cout << "\nDate of Birth : " << dob.day << "-" << dob.month << "-" << dob.year;
    
    cout << "\nAccount Number: " << getAccountNumber();
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
    gotoxy(60, 0);
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
    setAccountNumber();
}

void Show()
{
    Account test;
    test = readAccountInfo(110008, 0);
    test.getAccountNumber();
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
    Account test;
    // test.createAccount();
    // test.showAccountInfo();
    //test.setAccountNumber();
    //writeAccountInfo(test);
    // test.createAccount();
    MainMenu();
    //MainMenu();
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
        
        newAccount.createAccount();
        newAccount.showAccountInfo();
        writeAccountInfo(newAccount);

        break;
    case '2':
        
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
    userAccount = readAccountInfo(checkAccountNumber, &flag);
    if (flag == 1)
    {
        gotoxy(35, 41);
        cout << "Enter Password : ";
        cin >> checkPassword;
        
        if (strcmpi(userAccount.getPassword(),checkPassword)==0)
        {
            loginMenu(userAccount);
        }
        else
        {
            cout<<"\n Password INVALID\n";
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
    cout << "Enter your Choice : ";
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