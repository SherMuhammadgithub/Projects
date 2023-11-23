#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

// headers
void header();
void adminLoginHeader();
void signUpHeader();
void signInHeader();
void managerHeader();
void userHeader();
/// manager
int loginAsManager();
bool adminLoginCheck(string, string &);         ///////// we r here
/// manager functions
void viewRecords();
void addNewUser();
void deleteUser();
void setGoldRate();
/// user
void loginAsUser(string);
void greetUser(string);   
/// user functions
void depositMoney();
void checkPortfolio();
void transferMoney();
void withdrawMoney();
void investGold();
void viewTransactions();
void blockOrUnblockTransactions();
void modifyInformation();
void changePassword();
void deleteAccount();
/// menus
int mainMenu();
void signUpCheck();
bool signInValidate(string [], string [], int, string, string);
int managerMenu();
int userMenu();
/// sign up
void createUser(string userNames[], string userPasswords[], int &index, string name, string pass);
/// data Verification
bool uniqueUser(string[], int &, string);   /// sign up
bool userExist(string[], string, int);     /// sign in
bool checkUserValidity(string [], string [], int , string, string);  /// pass checker
///// error handling
void accountNotExists();
void passNotCorrect();

///// Global Variables
/// managers pass
// string adminPassword = "admin";             ////////////// remove
// // gold rate
// float goldRate = 63.69;               ////////////////// remove
// /// counter for index of arrays
// int index = 4;       //////////////////////////////////////////////// remove

// int currentIndex = 0;      /// to check currently user's index               //////////////// remove

// //// arrays for user data (remove after impletmenting in main)
// string userNames[100] = {"moon", "ateeb", "ali", "sheri"};        /// already registered user's       ;}   //// remove                                                                                                     
// string userPasswords[100] = {"admin", "admin", "admin", "admin"};         /// default passwords            //// remove                                                                                         
// string userIDs[100] = {"0001","0002","0003","0004"};                                                       //// remove                                                 
// float userBalances[100] = {100,200,400,800};                                                               //// remove                                         
// float userInvestments[100] = {0};                                                                          //// remove                              
// float transactions[100] = {0};           //// transactions history :|                                      //// remove                                                                 
// string transactionsTypes[100];                                                                             //// remove                          
// /////////////////////////////
// int transferIndex = 0;         /// for transfer of cash b/w users           ////////////////////// remove       
// int transactionsIndex = 0;       /// displaying transactions                ////////////////////// remove  
// bool blockTransactions = false;       /// for blocking transactions         ////////////////////// remove           
// int del = 0;    //// for deleting user info            //// don't remove this           

////////////////////////////////////////////////////////////////////////////////////////// Start of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    //// arrays for user data
    int index = 4;
    string userNames[100] = {"moon", "ateeb", "ali", "sheri"};
    string userPasswords[100] = {"admin", "admin", "admin", "admin"};
    string userIDs[100] = {"0001","0002","0003","0004"};
    float userBalances[100] = {100,200,400,800};
    float userInvestments[100] = {0};
    float transactions[100] = {0};           
    string transactionsTypes[100];
    /////////////////////////////////////////////////////////////
    ////// users 
    int currentIndex = 0;
    int transferIndex = 0;         /// for transfer of cash b/w users
    int transactionsIndex = 0;       /// displaying transactions
    bool blockTransactions = false;       /// for blocking transactions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////// admins
    string adminPassword = "admin";
    float goldRate = 63.69;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int choice = 0;
    string LogInTo = "null";
mainPage:       ///// for logging out of user's
    while(choice != 4)
    {
        choice = mainMenu();         //// menu bar option select
        if (choice == 1)             /// admin login
        { 
            adminLoginHeader();
            string userEnterAdminPass;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter the Password: ";
            cin >> userEnterAdminPass;
            bool login =  adminLoginCheck(userEnterAdminPass, adminPassword);
            if (login)
            {
                LogInTo = "admin";
                break;
            }
            else 
            {
                cout << "\n\t\t\t\t\t\t\t\t\t\t   Access Denied.............." << endl;
                cout << "\n\t\t\t\t\t\t\t\t\t\t   Press any key to continue..";
                getch();
            }
            // cout << login;
        }   
        else if (choice == 2)      /////sig in user
        {
            signInHeader();
            string userEnteredPassword, userEnteredName;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter your User Name: ";
            cin >> userEnteredName;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter your Password: ";
            cin >> userEnteredPassword;
            bool login = signInValidate(userNames, userPasswords, index, userEnteredName, userEnteredPassword);
            if (login)
            {
                LogInTo = "user"; 
                break;
            }
        }
        else if (choice == 3)   //// sign up user
        {
            signUpHeader();
            string name;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter your name: ";
            cin >> name;

            string pass;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter password: ";
            cin >> pass;

            if (uniqueUser(userNames, index ,name))         /// User created
                createUser(userNames, userPasswords, index, name, pass);
            else
                cout << "\n\t\t\t\t\t\t\t\t\t\t   User already exists..........";

            cout << "\n\t\t\t\t\t\t\t\t\t\t   Press any key to continue....";
            getch();
        }
        else if (choice == 4)
            return 0;                         /// end program
        else             /// for error cases
        { 
            cout << "\t\t\t\t\t\t\t\t\t\t   Invalid choice....";
            Sleep(500);
        }
}
    // loginAsUser("moon");         /// debugging purpose
    if (LogInTo == "admin")
    {
        int adminSelectedOption = 0;
        while(adminSelectedOption != 11)
        { 
            adminSelectedOption = managerMenu();
            if (adminSelectedOption == 1)
                addNewUser();
            if (adminSelectedOption == 2)
                viewRecords();
            else if (adminSelectedOption == 3)
            {   
                //// not complete
            }
            else if (adminSelectedOption == 4)
            {   
                //// not complete
            }
            else if (adminSelectedOption == 5)
                setGoldRate();
            else if (adminSelectedOption == 6)
            {   
                //// not complete
            }
            else if (adminSelectedOption == 7)
            {   
                //// not complete
            }
            else if (adminSelectedOption == 8)
            {   
                //// not complete
            }
            else if (adminSelectedOption == 9)
            {   
                //// not complete
            }
            else if (adminSelectedOption == 10)
            {   
                // del = 1;
                viewRecords();
                deleteUser();
            }
            else if (adminSelectedOption == 11)
            {
                goto mainPage;
            }
            else
            {
                cout << "\t\t\t\t\t\t\t\t\t\t  Invalid Choice...";
                Sleep(400);
            }
        }
    }
    else if (LogInTo == "user")
    {
        int userSelectedOption = 0;
        while(userSelectedOption != 11)
        {
            userSelectedOption = userMenu();
            if (userSelectedOption == 1)
                checkPortfolio();
            else if(userSelectedOption == 2)
                depositMoney();
            else if (userSelectedOption == 3)
                withdrawMoney();
            else if (userSelectedOption == 4)
                transferMoney();
            else if (userSelectedOption == 5)
                investGold();             
            else if (userSelectedOption == 6)
                viewTransactions();      
            else if (userSelectedOption == 7)
                blockOrUnblockTransactions();
            else if (userSelectedOption == 8)
                modifyInformation();
            else if (userSelectedOption == 9)
                changePassword();
            else if (userSelectedOption == 10)
                deleteAccount();
            else if (userSelectedOption == 11)
                goto mainPage;         // logout
            else 
            {
                cout << "\t\t\t\t\t\t\t\t\t\t  Invalid Choice...";
                Sleep(400);
            }   
        }
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tUnexpexted Error Occured......";
        return 0;
    }
}

void managerHeader()
{
    system("cls");
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Example: Set foreground color to green
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                             /'\_/`\                                                   )" << endl;
    cout << R"(                                                            /\      \     __      ___      __       __      __   _ __  )" << endl;
    cout << R"(                                                            \ \ \__\ \  /'__`\  /' _ `\  /'__`\   /'_ `\  /'__`\/\`'__\)" << endl;
    cout << R"(                                                             \ \ \_/\ \/\ \L\.\_/\ \/\ \/\ \L\.\_/\ \L\ \/\  __/\ \ \/ )" << endl;
    cout << R"(                                                              \ \_\\ \_\ \__/.\_\ \_\ \_\ \__/.\_\ \____ \ \____\\ \_\ )" << endl;
    cout << R"(                                                               \/_/ \/_/\/__/\/_/\/_/\/_/\/__/\/_/\/___L\ \/____/ \/_/ )" << endl;
    cout << R"(                                                                                                    /\____/            )" << endl;
    cout << R"(                                                                                                    \_/__/             )" << endl;
    cout << endl;
    cout << "                                                                ##########################################################" << endl;
    cout << endl;
    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}



/// input validations start
void passNotCorrect()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Invalid Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue...";
    getch();
}
void accountNotExists()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Account does'nt Exist" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue...";
    getch();
}
bool checkUserValidity(string userNames[], string userPasswords[], int index, string name, string pass)
{
    bool validPass = false;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i] && pass == userPasswords[i])
        {
            validPass = true;
            // currentIndex = i;
            break;
        }    
    }
    return validPass;
}
bool userExist(string userNames[], string name, int index)
{
    bool exists = false;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i])
        {
            exists = true;    
            // transferIndex = i;       // for transfer of cash  
            break;
        }
    }
    return exists;
}
bool uniqueUser(string userNames[], int &index, string name)
{
    bool unique = true;     
    for (int i = 0; i < index; i++)    // looping through names array to check if new user 
    {
        if (name == userNames[i])
        {
            unique = false;
            break;
        }
    }
    return unique;
}
/// input validation end
int mainMenu()             ///// complete
{
    header();
    int option;
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Login as Manager" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. Login as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. Sign up as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. End" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Please Select an Option...";
    cin >> option;
    return option;
}

void createUser(string userNames[], string userPasswords[], int &index, string name, string pass)
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Please wait Creating new user....";
    Sleep(1000);

    /// assigning values
    userNames[index] = name;
    userPasswords[index] = pass;
    // userBalances[index] = 0;
    // userIDs[index] = "000"; 
    // userIDs[index] += to_string(index+1);
    index++;  
    // cout << index << endl;
    cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t   Successfully created new user" << endl;
}

//////////////////////////////////////////////////////////////////////////////////////// start of signUp/signIn //////////////////////////////////////////////////////////////////////////////////////////////////////////
void signUpCheck()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Please wait Creating new user....";
    Sleep(1000);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t   User already exists" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue....";
    getch();
}
bool signInValidate(string userNames[], string userPasswords[], int index , string name, string pass)
{
    bool allowLogin = false;
    if (userExist(userNames, name, index))
    {
        if (checkUserValidity(userNames, userPasswords, index, name, pass))
            allowLogin = true;
            // loginAsUser(name);
        else
            passNotCorrect();
    }
    else
        accountNotExists();
    return allowLogin;
}
bool adminLoginCheck(string pass, string &adminPassword)
{
    bool login = false; 
    if (pass == adminPassword)
        login = true;
    return login;
}
/////////////////////////////////////////////////////////////////////////////////////// end of signUp/SignIn /////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////// manager loggedIn start ////////////////////////////////////////////////////////////////////////////////////////////////////////////
int managerMenu()
{
    managerHeader();
    int adminSelectedOption;
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Add a New User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. View All Records" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. View Single Record" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. Interest Calculator" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   5. Set Gold Rate" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   6. Loan Calculator" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   7. Give Loan" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   8. Update Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   9. Reset Passwords" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  10. Delete a User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  11. Log Out" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  Please Select an Option...";
    cin >> adminSelectedOption;
    return adminSelectedOption;
}

int loginAsManager()
{
    
}

/// manager functions defination
void addNewUser()
{
    header();
    signUpCheck();
    loginAsManager();
}
void setGoldRate()
{
    // header();
    // cout << "\t\t\t\t\t\t\t\t\t\tCurrent Rate of Gold per gram: " << goldRate;
    
    // float newGoldRate;
    // cout << "\n\n\t\t\t\t\t\t\t\t\t\tNew Gold Rate: ";
    // cin >> newGoldRate;

    // // goldRate = newGoldRate;

    // cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsManager();
}
void deleteUser()
{
    int choice;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the Sr. No you want to remove: ";
    cin >> choice;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait deleting the records...";
    Sleep(1000);
    
    // userNames[choice] = "";  /// just setting name to empty and not displaying it's all records on view record  ;}   
    // del = 0;
    
    header();
    viewRecords();
}
////////////////////////////////////////////////////////////////////////////////////// manager loggedIn end ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////// user loggedIn Start ///////////////////////////////////////////////////////////////////////////////////////////////////////////
void greetUser(string userName)
{
    cout << "\t\t\t\t\t\t\t\t\t\t   Welcome Back " << userName << endl;
}
int userMenu()
{    
    userHeader();
    greetUser("moon");
    cout << endl;
    int userOption;
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Check Portfolio" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. Deposit Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. With-Draw Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. Transfer Money To Another Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   5. Invest in Gold" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   5. Verify Account" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   5. View Account Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   6. View Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   7. Block/Unblock Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   8. Modify Information" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   8. Change Name" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   9. Change Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  10. Delete Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  11. Log Out" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  Please Select an Option...";
    cin >> userOption;
    return userOption;
}
void userHeader()
{
    system("cls");
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Example: Set foreground color to green
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                        __  __                          )" << endl;
    cout << R"(                                                                       /\ \/\ \                         )" << endl;
    cout << R"(                                                                       \ \ \ \ \    ____     __   _ __  )" << endl;
    cout << R"(                                                                        \ \ \ \ \  /',__\  /'__`\/\`'__\)" << endl;
    cout << R"(                                                                         \ \ \_\ \/\__, `\/\  __/\ \ \/ )" << endl;
    cout << R"(                                                                          \ \_____\/\____/\ \____\\ \_\ )" << endl;
    cout << R"(                                                                           \/_____/\/___/  \/____/ \/_/ )" << endl;
    cout << endl;
    cout << "                                                                             ##############################" << endl;
    cout << endl;
    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void loginAsUser(string userName)
{
    
}
/// user functions defination
void depositMoney()
{
    // header();
    // if (!blockTransactions)
    // {
    //     float deposit;
    //     cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Deposit: $";
    //     cin >> deposit;

    //     userBalances[currentIndex] += deposit;

    //     cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
    //     Sleep(1000);

    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully deposited \"$" << deposit << "\" into you're account." << endl;
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
        
    //     //// storing the transaction history
    //     transactions[transactionsIndex] = deposit;
    //     transactionsTypes[transactionsIndex] = "Deposit";
    //     transactionsIndex++;
    // }
    // else
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;

    // cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void transferMoney()
{
    // header();
    // if (!blockTransactions)
    // {
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalances[currentIndex] << endl << endl;

    //     float transfer;
    //     cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Transfer: $";
    //     cin >> transfer;

    //     string name;
    //     cout << "\t\t\t\t\t\t\t\t\t\tEnter name of the reciever: ";
    //     cin >> name;

    //     cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
    //     Sleep(1000);

    //     bool recieverExists = false;//false not here ---> oG code remove false after removing error //userExist(name);
    //     if (recieverExists)
    //     {
    //         if (transfer <= userBalances[currentIndex])
    //         {                                                       //// transfered
    //             userBalances[currentIndex] -= transfer;               //  from user1
    //             userBalances[transferIndex] += transfer;              //   to user2

    //             cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully Transfered \"$" << transfer << "\" from you're account to the account of \"" << userNames[transferIndex] << "\"" << endl;
    //             cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
                
    //             //// storing the transaction history
    //             transactions[transactionsIndex] = transfer;
    //             transactionsTypes[transactionsIndex] = "Transfer";
    //             transactionsIndex++;
    //         }
    //         else if (transfer > userBalances[currentIndex]) 
    //             cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
    //         else
    //             cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn error occured." << endl;          /// any error case
    //     }
    //     else
    //         cout << "\n\n\t\t\t\t\t\t\t\t\t\tNo such user exists in our database ;(" << endl;
    // }
    // else
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    
    // cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void withdrawMoney()
{
    header();
    // if (!blockTransactions)
    // {
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalances[currentIndex] << endl << endl;

    //     float withdraw;
    //     cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to With-Draw: $";
    //     cin >> withdraw;

    //     cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
    //     Sleep(1000);

    //     if (withdraw <= userBalances[currentIndex])
    //     {
    //         userBalances[currentIndex] -= withdraw;
    //         cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully With-Drawn \"$" << withdraw << "\" from you're account." << endl;
    //         cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
            
    //         //// storing the transaction history
    //         transactions[transactionsIndex] = withdraw;
    //         transactionsTypes[transactionsIndex] = "Withdraw";
    //         transactionsIndex++;
    //     }
    //     else if (withdraw > userBalances[currentIndex]) 
    //         cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
    //     else
    //         cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn error occured." << endl;          /// any error case
    // }
    // else
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    
    // cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void checkPortfolio()
{
    system("cls");
    cout << "HI";
    getch();
    // header();
    // cout << "\t\t\t\t\t\t\t\t\t\tCash: $" << userBalances[currentIndex] << endl;
    // if (userInvestments[currentIndex] != 0)
    // {
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tGold(in grams): " << userInvestments[currentIndex];
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tGold(in Dollars): " << userInvestments[currentIndex] * goldRate << endl;
    // }
    
    // cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void investGold()
{
    // header();
    // if (!blockTransactions)
    // {
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Balance: $" << userBalances[currentIndex] << endl << endl;
    //     cout << "\t\t\t\t\t\t\t\t\t\t1-Gram of Gold = $" << goldRate << endl  << endl;
        
    //     float investment;
    //     cout << "\t\t\t\t\t\t\t\t\t\tEnter amount you want to invest in Gold: $";
    //     cin >> investment;

    //     float goldinGrams = investment / goldRate;
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tYou will get " << goldinGrams << "-Gram of Gold.";

    //     int proceed;
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want to proceed\n\t\t\t\t\t\t\t\t\t\t1...YES\n\t\t\t\t\t\t\t\t\t\t2... NO: ";
    //     cin >> proceed;
    //     if (proceed == 1)
    //     {
    //         cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    //         Sleep(1000);
    //         if (investment <= userBalances[currentIndex] )
    //         {
    //             userBalances[currentIndex] -= investment;
    //             userInvestments[currentIndex] += goldinGrams;
    //             cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully invested \"$" << investment << "\" into " << goldinGrams << "-Gram of gold..";
    //             cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: " << userBalances[currentIndex];

    //             //// storing the transaction history
    //             transactions[transactionsIndex] = investment;
    //             transactionsTypes[transactionsIndex] = "Investment";
    //             transactionsIndex++;
    //         }
    //         else if (investment > userBalances[currentIndex])
    //             cout << "\n\n\t\t\t\t\t\t\t\t\t\tBalance is Low.";
    //         else
    //             cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn Error occured.. :/";

    //         cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    //         getch();
    //         loginAsUser(userNames[currentIndex]);
    //     }
    //     else if (proceed == 2)
    //     {
    //         cout << "\t\t\t\t\t\t\t\t\t\tPress any key to continue";
    //         getch();
    //         loginAsUser(userNames[currentIndex]);
    //     }
    //     else
    //         cout << "\t\t\t\t\t\t\t\t\t\tInvalid input.";
    // }
    // else
    //     cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    
    // cout << "\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void viewTransactions()
{
    // header();
    // if (transactions[0] != 0)
    // {
    //     cout << "\t\t\t\t\t\t\t\t       #################################################" << endl;
    //     cout << "\t\t\t\t\t\t\t\t\t  Transaction Type\t     Amount($)" << endl;
    //     cout << "\t\t\t\t\t\t\t\t       #################################################" << endl << endl;
    //     for (int i = 0; i < transactionsIndex; i++ )
    //     {
    //         cout << "\t\t\t\t\t\t\t\t\t     " << transactionsTypes[i] << "\t\t\t" << transactions[i] << endl;
    //     }
    // }
    // else
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tNo Transactions for Now..";
    
    // cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void blockOrUnblockTransactions()
{
    // header();
    // cout << "\t\t\t\t\t\t\t\t\t\tPlease wait...";
    // Sleep(1000);
    // if (blockTransactions == false)
    // {
    //     blockTransactions = true;
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour Transactions have been Blocked.";
    // }
    // else
    // {   
    //     blockTransactions = false;     
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour Transactions have been Unblocked.";
    // }
    // cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void modifyInformation()
{
    // header();
    
    // string currentPass;
    // cout << "\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    // cin >> currentPass;
    
    // cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    // Sleep(1000);
    
    // if(currentPass == userPasswords[currentIndex])
    // {
    //     string newName;
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
    //     cin >> newName;

    //     cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    //     Sleep(1000);
    
  ///error here so commented      // if(!userExist(newName))                    /// does'nt exist
        // {
        //     string oldName = userNames[currentIndex];         //// optional for output :]
        //     userNames[currentIndex] = newName;
        //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're name was successfully changed from \"" << oldName << "\" to " << "\"" << newName << "\"";
        // }
        // else
        //     cout << "\n\t\t\t\t\t\t\t\t\t\tUser Already Exists..";
    // }
    // else
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    // cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void changePassword()
{
    // header();
    
    // string currentPass;
    // cout << "\t\t\t\t\t\t\t\t\t\tEnter Current Password: ";
    // cin >> currentPass;
    
    // cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    // Sleep(1000);
    
    // if(currentPass == userPasswords[currentIndex])
    // {
    //     string newPass;
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tEnter New Password: ";
    //     cin >> newPass;
    //     userPasswords[currentIndex] = newPass;
    //     cout << "\n\t\t\t\t\t\t\t\t\t\tPassword Successfully changed..";
    // }
    // else
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    // cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void deleteAccount()
{
    // header();
    
    // string currentPass;
    // cout << "\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    // cin >> currentPass;
    
    // cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    // Sleep(1000);
    
    // if(currentPass == userPasswords[currentIndex])
    // {
    //     userNames[currentIndex] = "";         /// deleting name so can't access this account now     ;}
        
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour account has been removed.";
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    //     getch();
    //     mainMenu();
    // }
    // else
    //     cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    // cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    // getch();
    // loginAsUser(userNames[currentIndex]);
}
void viewRecords()
{
    // header();
    // cout << "\t\t\t\t\t\t\t\t\t   #################################################" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t    Sr No\t NAME \t    ID - No. \t Balance($)" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t   #################################################" << endl;
    // cout << endl;
    // for (int i = 0; i < index; i++)
    // {
    //     if (userNames[i] != "")
    //         cout << "\t\t\t\t\t\t\t\t\t      " << i << " \t " << userNames[i] << "\t      " << userIDs[i] << "\t   " << userBalances[i] << endl;
    //     else   
    //         continue;
    // }
    // if (del==0)
    // {
    //     cout << "\n\t\t\t\t\t\t\t\t\tPress any key to continue...";
    //     getch();
    // }
}
//////////////////////////////////////////////////////////////////////////////////////////////// user loggedIn End ///////////////////////////////////////////////////////////////////////////////////////////////////////

void header()
{
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Example: Set foreground color to green
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

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
    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void signInHeader()
{
    system("cls");
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Example: Set foreground color to green
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                     ____                                      )" << endl;
    cout << R"(                                                                    /\  _`\   __                               )" << endl;
    cout << R"(                                                                    \ \,\L\_\/\_\     __     ___               )" << endl;
    cout << R"(                                                                     \/_\__ \\/\ \  /'_ `\ /' _ `\             )" << endl;
    cout << R"(                                                                       /\ \L\ \ \ \/\ \L\ \/\ \/\ \            )" << endl;
    cout << R"(                                                                       \ `\____\ \_\ \____ \ \_\ \_\           )" << endl;
    cout << R"(                                                                        \/_____/\/_/\/___L\ \/_/\/_/           )" << endl;
    cout << R"(                                                                                      /\____/                  )" << endl;
    cout << R"(                                                                                      \_/__/                   )" << endl;
    cout << R"(                                                                                ______                         )" << endl;
    cout << R"(                                                                               /\__  _\                        )" << endl;
    cout << R"(                                                                               \/_/\ \/     ___                )" << endl;
    cout << R"(                                                                                  \ \ \   /' _ `\              )" << endl;
    cout << R"(                                                                                   \_\ \__/\ \/\ \             )" << endl;
    cout << R"(                                                                                   /\_____\ \_\ \_\            )" << endl;
    cout << R"(                                                                                   \/_____/\/_/\/_/            )" << endl;
    cout << endl;
    cout << "                                                                            ################################" << endl << endl;
  
    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void signUpHeader()
{
    system("cls");
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Example: Set foreground color to green
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << R"(                                                                      ____                                      )" << endl;
    cout << R"(                                                                     /\  _`\   __                               )" << endl;
    cout << R"(                                                                     \ \,\L\_\/\_\     __     ___               )" << endl;
    cout << R"(                                                                      \/_\__ \\/\ \  /'_ `\ /' _ `\             )" << endl;
    cout << R"(                                                                        /\ \L\ \ \ \/\ \L\ \/\ \/\ \            )" << endl;
    cout << R"(                                                                        \ `\____\ \_\ \____ \ \_\ \_\           )" << endl;
    cout << R"(                                                                         \/_____/\/_/\/___L\ \/_/\/_/           )" << endl;
    cout << R"(                                                                                       /\____/                  )" << endl;
    cout << R"(                                                                                       \_/__/                   )" << endl;
    cout << R"(                                                                                 __  __                         )" << endl;
    cout << R"(                                                                                /\ \/\ \                        )" << endl;
    cout << R"(                                                                                \ \ \ \ \  _____                )" << endl;
    cout << R"(                                                                                 \ \ \ \ \/\ '__`\              )" << endl;
    cout << R"(                                                                                  \ \ \_\ \ \ \L\ \             )" << endl;
    cout << R"(                                                                                   \ \_____\ \ ,__/             )" << endl;
    cout << R"(                                                                                    \/_____/\ \ \/              )" << endl;
    cout << R"(                                                                                             \ \_\              )" << endl;
    cout << R"(                                                                                              \/_/              )" << endl;
    cout << endl;
    cout << "                                                                            ################################" << endl << endl;
    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void adminLoginHeader()
{
    system("cls");
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Example: Set foreground color to green
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    cout << R"(                                                                    ______      __                                  )" << endl;
    cout << R"(                                                                   /\  _  \    /\ \              __                 )" << endl;
    cout << R"(                                                                   \ \ \L\ \   \_\ \    ___ ___ /\_\    ___         )" << endl;
    cout << R"(                                                                    \ \  __ \  /'_` \ /' __` __`\/\ \ /' _ `\       )" << endl;
    cout << R"(                                                                     \ \ \/\ \/\ \L\ \/\ \/\ \/\ \ \ \/\ \/\ \      )" << endl;
    cout << R"(                                                                      \ \_\ \_\ \___,_\ \_\ \_\ \_\ \_\ \_\ \_\     )" << endl;
    cout << R"(                                                                       \/_/\/_/\/__,_ /\/_/\/_/\/_/\/_/\/_/\/_/     )" << endl;
    cout << R"(                                                                                                                    )" << endl;
    cout << R"(                                                                                                                    )" << endl;
    cout << R"(                                                                           __                                       )" << endl;
    cout << R"(                                                                          /\ \                      __              )" << endl;
    cout << R"(                                                                          \ \ \        ___      __ /\_\    ___      )" << endl;
    cout << R"(                                                                           \ \ \  __  / __`\  /'_ `\/\ \ /' _ `\    )" << endl;
    cout << R"(                                                                            \ \ \L\ \/\ \L\ \/\ \L\ \ \ \/\ \/\ \   )" << endl;
    cout << R"(                                                                             \ \____/\ \____/\ \____ \ \_\ \_\ \_\  )" << endl;
    cout << R"(                                                                              \/___/  \/___/  \/___L\ \/_/\/_/\/_/  )" << endl;
    cout << R"(                                                                                                /\____/             )" << endl;
    cout << R"(                                                                                                \_/__/              )" << endl;
    cout << endl;
    cout << "                                                                              #########################################" << endl << endl;
    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
////////////////////////////////////////////////////////////////////////////////////////// End of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////