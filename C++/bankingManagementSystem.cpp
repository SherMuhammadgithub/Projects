#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//headers
void header();
int loginAsManager();
void loginAsUser(string);

/// manager functions
void viewRecords();
void addNewUser();
void deleteUser();

/// user functions
void depositMoney();
void checkMoney();
void transferMoney();
void withdrawMoney();
void applyLoan();
void viewTransactions();
void blockORunblockTransactions();
void modifyInformation();
void changePassword();
void deleteAccount();

/// menus
void mainMenu();
void signUpMainMenu();
void signInMainMenu();
void managerMenu();
void managerMainMenu();
void userMenu();

bool uniqueUser(string);   /// sign up
bool userExist(string);     /// sign in
bool checkUserValidity(string, string);  /// pass checker
void greetUser(string);   

///// errors handling
void accountNotExists();
void passNotCorrect();

//// Global Variables

/// managers pass
string managerPassword = "admin";

/// counter for index of arrays
int index = 4;
int currentIndex = 0;      /// to check currently user's index

//// arrays for data
string userNames[100] = {"moon", "ateeb", "ali", "sheri"};        /// already registered user's       ;}
string userPasswords[100] = {"admin", "admin", "admin", "admin"};         /// default passwords
float userBalance[100] = {100,200,400,800};
string userID[100] = {"0001","0002","0003","0004"};

////
int transferIndex = 0;    /// for transfer of cash b/w users
bool blockTransactions = false;       /// for blocking transactions

main()
{
    ////  ;)
    mainMenu();
}

void mainMenu()
{
    
    header();
    int choice;
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Login as Manager" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. Login as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. Sign up as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. End" << endl;

    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Please Select an Option...";

    cin >> choice;

    if (choice == 1)
    {
        managerMainMenu();
    }
    else if (choice == 2)
    {
        signInMainMenu();
    }
    else if (choice == 3)
    {
        signUpMainMenu();
        mainMenu();
    }
    else if (choice == 4)
    {
        return;  /// end program
    }
    else             /// error case
    { 
        cout << "\n\t\t\t\t\t\t\t\t\t\t   Invalid choice....";
        Sleep(500);
        mainMenu();
    }
}

void managerMainMenu()
{
    header();

    string password;
    cout << "\t\t\t\t\t\t\t\t\t\t   Enter the Password: ";
    cin >> password;
    
    if (password == managerPassword)
    {
        
        header();
        loginAsManager();
    }
    else{
        cout << "\n\t\t\t\t\t\t\t\t\t\t   Access Denied.." << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t   press any key to continue....";
        getch();
        mainMenu();
    }
}

void signInMainMenu()
{
    
    header();
    string password, userName;

    cout << "\t\t\t\t\t\t\t\t\t\t   Enter your User Name: ";
    cin >> userName;
    
    cout << "\t\t\t\t\t\t\t\t\t\t   Enter your Password: ";
    cin >> password;
    
    if (userExist(userName))
    {
        if (checkUserValidity(userName, password))
            loginAsUser(userName);
        else
            passNotCorrect();
    }
    else
        accountNotExists();
}

void passNotCorrect()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Invalid Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue...";
    getch();
    mainMenu();
}

void accountNotExists()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Account does'nt Exist" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue...";
    getch();
    mainMenu();
}

bool checkUserValidity(string name, string pass)
{
    bool validPass = true;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i] && pass == userPasswords[i])
        {
            validPass = true;
            currentIndex = i;
            break;
        }
        else
            validPass = false;    
    }
    return validPass;
}

bool userExist(string name)
{
    bool exists = true;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i])
        {
            exists = true;    
            transferIndex = i;       // for transfer of cash  
            break;
        }
        else
            exists = false;
    }
    return exists;
}

void signUpMainMenu()
{
    
    header();
    
    string name;
    cout << "\t\t\t\t\t\t\t\t\t\t   Enter your name: ";
    cin >> name;
    
    string pass;
    cout << "\t\t\t\t\t\t\t\t\t\t   Enter password: ";
    cin >> pass;

    if (uniqueUser(name))         /// User created
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\t   Please wait Creating new user....";
        Sleep(1000);

        /// assigning values
        userNames[index] = name;
        userPasswords[index] = pass;
        userBalance[index] = 0;
        userID[index] = "000"; 
        userID[index] += to_string(index+1);

        index++;      /// changing global index to new value
        
        cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t   Successfully created new user" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue....";
        getch();
    }
    else          /// user not created
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\t   Please wait Creating new user....";
        Sleep(1000);

        cout << "\n\n\t\t\t\t\t\t\t\t\t\t   User already exists" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue....";
        getch();
    }
}

bool uniqueUser(string name)
{
    bool unique = true;     
    for (int i = 0; i < index; i++)    // looping through names array to check if new user 
    {
        if (name == userNames[i])
            unique = false;
    }
    return unique;
}

void addNewUser()
{
    header();
    signUpMainMenu();
    loginAsManager();
}

int del = 0;
int loginAsManager()
{
    while(true)
    {
        header();
        
        managerMenu();
        
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            addNewUser();
        }
        if (choice == 2)
        {
            viewRecords();
        }   
        else if (choice == 3)
        {   
            
        }
        else if (choice == 4)
        {   
            
        }
        else if (choice == 5)
        {  

        }
        else if (choice == 6)
        {   

        }
        else if (choice == 7)
        {   
                        
        }
        else if (choice == 8)
        {   
                
        }
        else if (choice == 9)
        {   
        
        }
        else if (choice == 10)
        {   
            del = 1;
            viewRecords();
            deleteUser();
        }
        else if (choice == 11)
        {
            mainMenu();
            return 0;
        }
        else
        {
            cout << "Invalid";
            return 0;
        }
    }
}

void managerMenu()
{
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Add a New User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. View All Records" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. View Single Record" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. Interest Calculator" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   5. Set Interest Rate" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   6. Loan Calculator" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   7. Give Loan" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   8. Update Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   9. Reset Passwords" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  10. Delete a User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  11. Back" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Please Select an Option...";
}

void deleteUser()
{
    int choice;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the Sr. No you want to remove: ";
    cin >> choice;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait deleting the records...";
    Sleep(1000);
    
    userNames[choice] = "";  /// just setting name to empty and not displaying it's all records on view record  ;}   
    del = 0;
    
    header();
    viewRecords();
}


void depositMoney()
{
    header();

    float deposit;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Deposit: $";
    cin >> deposit;
    
    userBalance[currentIndex] += deposit;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
    Sleep(1000);

    cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully deposited \"$" << deposit << "\" into you're account." << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalance[currentIndex] << endl;

    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void transferMoney()
{
    header();
    
    cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalance[currentIndex] << endl << endl;
    
    float transfer;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Transfer: $";
    cin >> transfer;

    string name;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter name of the reciever: ";
    cin >> name;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
    Sleep(1000);
    
    bool recieverExists = userExist(name);
    if (recieverExists)
    {
        if (transfer <= userBalance[currentIndex])
        {                                                       //// transfered
            userBalance[currentIndex] -= transfer;               //  from user1
            userBalance[transferIndex] += transfer;              //   to user2

            cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully Transfered \"$" << transfer << "\" from you're account to the account of \"" << userNames[transferIndex] << "\"" << endl;
            cout << "\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalance[currentIndex] << endl;
        }
        else if (transfer > userBalance[currentIndex]) 
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
        else
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn error occured." << endl;          /// any error case
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tNo such user exists in our database ;(" << endl;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void withdrawMoney()
{
    header();
    
    cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalance[currentIndex] << endl << endl;
    
    float withdraw;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to With-Draw: $";
    cin >> withdraw;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
    Sleep(1000);

    if (withdraw <= userBalance[currentIndex])
    {
        userBalance[currentIndex] -= withdraw;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully With-Drawn \"$" << withdraw << "\" from you're account." << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalance[currentIndex] << endl;
    }
    else if (withdraw > userBalance[currentIndex]) 
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn error occured." << endl;          /// any error case

    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void checkMoney()
{
    header();
    cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalance[currentIndex] << endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void loginAsUser(string userName)
{
    header();   
    greetUser(userName);
    cout << endl;

    userMenu();
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        checkMoney();
    }
    else if(choice == 2)
    {
        depositMoney();
    }
    else if (choice == 3)
    {
        withdrawMoney();
    }
    else if (choice == 4)
    {
        transferMoney();
    }
    else if (choice == 5)
    {
        applyLoan();             /// not complete
    }
    else if (choice == 6)
    {
        viewTransactions();      /// not complete
    }
    else if (choice == 7)
    {
        blockORunblockTransactions();     /// not complete
    }
    else if (choice == 8)
    {
        modifyInformation();
    }
    else if (choice == 9)
    {
        changePassword();
    }
    else if (choice == 10)
    {
        deleteAccount();
    }
    else if (choice == 11)
    {
        mainMenu();
    }
}

void userMenu()
{    
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Check Balance" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. Deposit Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. With-Draw Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. Transfer Money To Another Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   5. Apply for a Loan" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   5. Verify Account" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   5. View Account Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   6. View Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   7. Block/Unblock Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   8. Modify Information" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   8. Change Name" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   9. Change Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  10. Delete Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  11. Back" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Please Select an Option...";

}

void greetUser(string userName)
{
    cout << "\t\t\t\t\t\t\t\t\t\t   Welcome Back " << userName << endl;
}

void applyLoan()
{

}

void viewTransactions()
{

}

void blockORunblockTransactions()
{
    if (blockTransactions == false)
        blockTransactions = true;
    else
        blockTransactions = false;    
}

void modifyInformation()
{
    header();
    
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    cin >> currentPass;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    Sleep(1000);
    
    if(currentPass == userPasswords[currentIndex])
    {
        string newName;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
        cin >> newName;

        cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
        Sleep(1000);
    
        if(!userExist(newName))                    /// does'nt exist
        {
            string oldName = userNames[currentIndex];         //// optional for output :]
            userNames[currentIndex] = newName;
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're name was successfully changed from \"" << oldName << "\" to " << "\"" << newName << "\"";
        }
        else
            cout << "\n\t\t\t\t\t\t\t\t\t\tUser Already Exists..";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void changePassword()
{
    header();
    
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter Current Password: ";
    cin >> currentPass;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    Sleep(1000);
    
    if(currentPass == userPasswords[currentIndex])
    {
        string newPass;
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter New Password: ";
        cin >> newPass;
        userPasswords[currentIndex] = newPass;
        cout << "\n\t\t\t\t\t\t\t\t\t\tPassword Successfully changed..";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void deleteAccount()
{
    header();
    
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    cin >> currentPass;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    Sleep(1000);
    
    if(currentPass == userPasswords[currentIndex])
    {
        userNames[currentIndex] = "";         /// deleting name so can't access this account now     ;}
        
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour account has been removed.";
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
        getch();
        mainMenu();
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    loginAsUser(userNames[currentIndex]);
}

void viewRecords()
{
    header();
    cout << "\t\t\t\t\t\t\t\t\t   #################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t    Sr No\t NAME \t    ID - No. \t Balance($)" << endl;
    cout << "\t\t\t\t\t\t\t\t\t   #################################################" << endl;
    cout << endl;
    for (int i = 0; i < index; i++)
    {
        if (userNames[i] != "")
            cout << "\t\t\t\t\t\t\t\t\t      " << i << " \t " << userNames[i] << "\t      " << userID[i] << "\t   " << userBalance[i] << endl;
        else   
            continue;
    }
    if (del==0)
    {
        cout << "\n\t\t\t\t\t\t\t\t\tPress any key to continue...";
        getch();
    }
}

void header()
{
    system("cls");
    cout << R"(                                                                       ____                     __                                      )" << endl;
    cout << R"(                                                                      /\  _`\                  /\ \                                     )" << endl;
    cout << R"(                                                                      \ \ \L\ \     __      ___\ \ \/'\                                 )" << endl;
    cout << R"(                                                                       \ \  _ <'  /'__`\  /' _ `\ \ , <                                 )" << endl;
    cout << R"(                                                                        \ \ \L\ \/\ \L\.\_/\ \/\ \ \ \\`\                               )" << endl;
    cout << R"(                                                                         \ \____/\ \__/.\_\ \_\ \_\ \_\ \_\                             )" << endl;
    cout << R"(                                                                          \/___/  \/__/\/_/\/_/\/_/\/_/\/_/                   __        )" << endl;
    cout << R"(                                                  /'\_/`\                                                                    /\ \__     )" << endl;
    cout << R"(                                                 /\      \     __      ___      __       __      __    ___ ___      __    ___\ \ ,_\    )" << endl;
    cout << R"(                                                 \ \ \__\ \  /'__`\  /' _ `\  /'__`\   /'_ `\  /'__`\/' __` __`\  /'__`\/' _ `\ \ \/    )" << endl;
    cout << R"(                                                  \ \ \_/\ \/\ \L\.\_/\ \/\ \/\ \L\.\_/\ \L\ \/\  __//\ \/\ \/\ \/\  __//\ \/\ \ \ \_   )" << endl;
    cout << R"(                                                   \ \_\\ \_\ \__/.\_\ \_\ \_\ \__/.\_\ \____ \ \____\ \_\ \_\ \_\ \____\ \_\ \_\ \__\  )" << endl;
    cout << R"(                                                    \/_/ \/_/\/__/\/_/\/_/\/_/\/__/\/_/\/___L\ \/____/\/_/\/_/\/_/\/____/\/_/\/_/\/__/  )" << endl;
    cout << R"(                                                                                         /\____/                                        )" << endl;
    cout << R"(                                                                                         \_/__/                                         )" << endl;
    cout << R"(                                                                      ____                     __                                       )" << endl;
    cout << R"(                                                                     /\  _`\                  /\ \__                                    )" << endl;
    cout << R"(                                                                     \ \,\L\_\  __  __    ____\ \ ,_\    __    ___ ___                  )" << endl;
    cout << R"(                                                                      \/_\__ \ /\ \/\ \  /',__\\ \ \/  /'__`\/' __` __`\                )" << endl;
    cout << R"(                                                                        /\ \L\ \ \ \_\ \/\__, `\\ \ \_/\  __//\ \/\ \/\ \               )" << endl;
    cout << R"(                                                                        \ `\____\/`____ \/\____/ \ \__\ \____\ \_\ \_\ \_\              )" << endl;
    cout << R"(                                                                         \/_____/`/___/> \/___/   \/__/\/____/\/_/\/_/\/_/              )" << endl;
    cout << R"(                                                                                    /\___/                                              )" << endl;
    cout << R"(                                                                                    \/__/                                               )" << endl;
    cout << endl;
    cout << "                                                                  ############################################################             " << endl; 
    cout << endl;
}

/////old header
    // cout << "                                                               ######       ####     ###    ##   ##   ##                                     " << endl;
    // cout << "                                                               ##    ##   ##    ##   ## #   ##   ##  ##                                      " << endl;
    // cout << "                                                               ######     ## ## ##   ##  #  ##   ####                                        " << endl;
    // cout << "                                                               ##    ##   ##    ##   ##   # ##   ##  ##                                      " << endl;
    // cout << "                                                               ######     ##    ##   ##    ###   ##   ##                                     " << endl;
    
    // cout << endl;
                
    // cout << "                                ###   ###     ####     ###    ##     ####      ######     #####   ###   ###    #####   ###    ##   ########  " << endl; 
    // cout << "                                ## # # ##   ##    ##   ## #   ##   ##    ##   ##         ##       ## # # ##   ##       ## #   ##      ##     " << endl; 
    // cout << "                                ##  #  ##   ## ## ##   ##  #  ##   ## ## ##   ##  ###    ####     ##  #  ##   ####     ##  #  ##      ##     " << endl; 
    // cout << "                                ##     ##   ##    ##   ##   # ##   ##    ##   ##    ##   ##       ##     ##   ##       ##   # ##      ##     " << endl; 
    // cout << "                                ##     ##   ##    ##   ##    ###   ##    ##    ######     #####   ##     ##    #####   ##    ###      ##     " << endl;

    // cout << endl; 
    
    // cout << "                                                         #####   ##    ##    #####   ########    #####   ###   ###                           " << endl; 
    // cout << "                                                        #         ##  ##    #           ##      ##       ## # # ##                           " << endl; 
    // cout << "                                                         ####       ##       ####       ##      ####     ##  #  ##                           " << endl; 
    // cout << "                                                             #      ##           #      ##      ##       ##     ##                           " << endl; 
    // cout << "                                                        #####       ##      #####       ##       #####   ##     ##                           " << endl;
    // cout                                                                                                                                                    << endl;
    // cout                                                                                                                                                    << endl;
    // cout                                                                                                                                                    << endl;
