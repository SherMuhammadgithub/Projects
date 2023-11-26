////////////////////////////////////////////////////////////////////////////////////////// Start of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>
#include <iomanip>
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
bool adminLoginCheck(string, string &);         
/// manager functions
bool addNewUser(string userNames[], string userPasswords[], string userIDs[], int &index, string, string);
void viewRecords(string userNames[], string userIDs[], float userBalances[] ,int index ,int del);
int addAsset(string [], string [],int, string, string);
void deleteUser(string [], int);
int liquidity(float userBalances[], int index);
void viewAssets(string [], string [], int);
int setNewGoldRate();
string resetAdminPassword(string adminPassword, string);
void modifyInfoAdmin(string userNames[], int index, int &transferIndex);
float giveLoan(float userBalances[],int index);
//////////////////////// user
void greetUser(string);   
/// user functions
void checkPortfolio(float userInvestments[], float userBalances[], int currentIndex, float goldRate);
void depositMoney(float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex, bool blockTransactions);
void withdrawMoney(float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex, bool blockTransactions);
void transferMoney(string userNames[], float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex,int &transferIndex, bool blockTransactions, int index);
void investGold(string userNames[],float userInvestments[], float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex, bool blockTransactions, int index, float goldRate);
void viewTransactions(string transactionsTypes[], float transactions[], int transactionsIndex);
bool blockOrUnblockTransactions(bool);
void modifyInformation(string userNames[], string userPasswords[], int currentIndex, int index, int &transferIndex);
void changePassword(string userPasswords[], int currentIndex);
bool deleteAccount(string userNames[], string userPasswords[],int currentIndex);
/// menus
int mainMenu();
void signUpCheck();
int managerMenu();
int userMenu();
/// sign up
void createUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass);
/// data Verification
bool uniqueUser(string[], int &, string);   /// sign up
bool userExist(string[], string, int, int &transferIndex);     /// sign in
bool checkUserValidity(string [], string [], int , int &, string, string);  /// pass checker
///// error handling
void accountNotExists();
void passNotCorrect();
///// 
string getAnonymousPass();
int againExecuteThisFunction();
void viewRecordHeader();
void adminPressAnyKey();
void userPressAnyKey();

//////////////////////////////////////////////////////////////////////////////////////   main function start    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    //// arrays for user data
    int index = 4;                                                    /// counter for the storing values
    string userNames[100] = {"moon", "ateeb", "ali", "sheri"};
    string userPasswords[100] = {"admin", "admin", "admin", "admin"};
    string userIDs[100] = {"0001","0002","0003","0004"};
    float userBalances[100] = {100,200,400,800};
    float userInvestments[100] = {0};
    float transactions[100] = {0};           
    string transactionsTypes[100];
    /////// bank assets
    string bankAssets[100] = {"Real-Estate","Bitcoin"};
    string bankAssetsWorth[100] = {"500k","100k"};
    int assetIndex = 2;
    ///////////////////////////////////////////////////////////////////
    ////// users extra vars
    int currentIndex = 0;
    int transferIndex = 0;                           /// for transfer of cash b/w users
    int transactionsIndex = 0;                          /// displaying transactions
    bool blockTransactions = false;                        /// for blocking transactions
    ////// admmins extra vars
    string adminPassword = "admin";
    float goldRate = 63.69;
    int del = 0;                                     ////// for deletion of records
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
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
            userEnterAdminPass = getAnonymousPass();       /// pass in  '***' format
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
        }   
        else if (choice == 2)      /////sig in user
        {
            signInHeader();
            string userEnteredPassword, userEnteredName;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter your User Name: ";
            cin >> userEnteredName;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter your Password: ";
            userEnteredPassword = getAnonymousPass();
            if (userExist(userNames, userEnteredName, index, transferIndex))
            {
                if (checkUserValidity(userNames, userPasswords, index, currentIndex, userEnteredName, userEnteredPassword))     /// password and name checking
                {
                    LogInTo = "user";       /// login successful
                    break;
                }
                else
                    passNotCorrect();
            }
            else
                accountNotExists();
        }
        else if (choice == 3)   //// sign up user
        {
            signUpHeader();
            string name;
            cout << "\t\t\t\t\t\t\t\t\t\t   Enter your name: ";
            cin >> name;

            string pass;
            cout << "\t\t\t\t\t\t\t\t\t\t   Set password: ";
            pass = getAnonymousPass();

            if (uniqueUser(userNames, index ,name))         /// User created
                createUser(userNames, userPasswords, userIDs, index, name, pass);
            else
                cout << "\n\t\t\t\t\t\t\t\t\t\t   User already exists..........";

            cout << "\n\t\t\t\t\t\t\t\t\t\t   Press any key to continue....";
            getch();
        }
        else if (choice == 4)
        {
            cout << "\t\t\t\t\t\t\t\t\t\t   Terminating the program....";
            Sleep(1000);
            system("cls");
            return 0;                         /// end program
        }
        else             /// for error cases
        { 
            cout << "\t\t\t\t\t\t\t\t\t\t   Invalid choice....";
            Sleep(500);
        }
    }
    if (LogInTo == "admin")
    {
        int adminSelectedOption = 0;
        while(adminSelectedOption != 11)
        { 
            adminSelectedOption = managerMenu();
            if (adminSelectedOption == 1)
            {
                bool again = true;
                while (again)        /// loop is for the admin if he want to add more then "1" user
                {
                    managerHeader();
                    string newUserName, newUserPass;
                    cout << "\t\t\t\t\t\t\t\t\t\t   Enter the Name: ";
                    cin >> newUserName;
                    cout << "\t\t\t\t\t\t\t\t\t\t   Set Password: ";
                    newUserPass =  getAnonymousPass();
                    again = addNewUser(userNames, userPasswords, userIDs, index, newUserName, newUserPass);
                }
            }
            else if (adminSelectedOption == 2)
            {
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances ,index , del);      
            }
            else if (adminSelectedOption == 3)
            {   
                managerHeader();
                string assetName;
                cout << "\t\t\t\t\t\t\t\t\tEnter the assest's name you want to add: ";
                cin >> assetName;
                string assetWorth;
                cout << "\t\t\t\t\t\t\t\t\tEnter the assest's worth you have added in (***k) format: ";
                cin >> assetWorth;
                assetIndex = addAsset(bankAssets, bankAssetsWorth, assetIndex, assetName, assetWorth);  // increasing the asset index by value return
            }
            else if (adminSelectedOption == 4)
            {   
                managerHeader();
                int cashHoldings = liquidity(userBalances, index);
                cout << "\t\t\t\t\t\t\t\t\tTotal Cash available in Liquid: " << cashHoldings << endl;
                adminPressAnyKey();
            }
            else if (adminSelectedOption == 5)
            {   
                managerHeader();
                cout << "\t\t\t\t\t\t\t\t\tCurrent Rate of Gold per gram: " << goldRate;
                goldRate = setNewGoldRate();       
                adminPressAnyKey();
            }
            else if (adminSelectedOption == 6)
            {   
                managerHeader();
                cout << "\t\t\t\t\t\t\t\t\tAsset's Name\t\t\tAsset's Worth($)\n";
                viewAssets(bankAssets, bankAssetsWorth, assetIndex);
                adminPressAnyKey();
            }
            else if (adminSelectedOption == 7)
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                int loanIndex;
                cout << "\n\t\t\t\t\t\t\t\t\t     Enter the Sr.No you want to give loan to: ";
                cin >> loanIndex;
                userBalances[loanIndex] = giveLoan(userBalances, loanIndex);
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == 8)
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                modifyInfoAdmin(userNames, index, transferIndex);
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == 9)
            {   
                managerHeader();
                string userEnteredAdminpass;
                cout << "\t\t\t\t\t\t\t\t\tEnter your current Password: ";
                userEnteredAdminpass = getAnonymousPass();
                adminPassword = resetAdminPassword(adminPassword, userEnteredAdminpass);
            }
            else if (adminSelectedOption == 10)
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                int deletionIndex;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to remove: ";
                cin >> deletionIndex;
                deleteUser(userNames, deletionIndex);
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == 11)
            {
                goto mainPage;     /// logging out
            }
            else
            {
                cout << "\t\t\t\t\t\t\t\t\t\t  Invalid Choice...";      /// invalid input
                Sleep(400);
            }
        }
    }
    else if (LogInTo == "user")
    {
        int userSelectedOption = 0;
        while(userSelectedOption != 11)
        {
            userHeader();
            greetUser(userNames[currentIndex]);
            cout << endl;
            userSelectedOption = userMenu();
            cout << endl;
            if (userSelectedOption == 1)
            {
                userHeader();
                checkPortfolio(userInvestments, userBalances, currentIndex, goldRate);
                userPressAnyKey();
            }
            else if(userSelectedOption == 2)
            {
                depositMoney(userBalances, transactions, transactionsTypes, currentIndex, transactionsIndex, blockTransactions);
            }
            else if (userSelectedOption == 3)
            {
                withdrawMoney(userBalances, transactions, transactionsTypes, currentIndex, transactionsIndex, blockTransactions);
            }
            else if (userSelectedOption == 4)
            {
                transferMoney(userNames, userBalances, transactions, transactionsTypes, currentIndex, transactionsIndex, transferIndex, blockTransactions, index);            
            }
            else if (userSelectedOption == 5)
            {
                investGold(userNames, userInvestments, userBalances, transactions, transactionsTypes, currentIndex, transactionsIndex, blockTransactions, index, goldRate);             
            }
            else if (userSelectedOption == 6)
            {
                viewTransactions(transactionsTypes, transactions, transactionsIndex);
            }
            else if (userSelectedOption == 7)
            {
                userHeader();
                blockTransactions = blockOrUnblockTransactions(blockTransactions);
                if(blockTransactions == true)
                    cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour Transactions have been Blocked.";
                else
                    cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour Transactions have been Unblocked.";
                userPressAnyKey();
            }
            else if (userSelectedOption == 8)
            {
                modifyInformation(userNames, userPasswords, currentIndex, index, transferIndex);
            }
            else if (userSelectedOption == 9)
            {
                changePassword(userPasswords, currentIndex);
            }
            else if (userSelectedOption == 10)
            {
                bool confirmDelete = deleteAccount(userNames, userPasswords, currentIndex);
                if (confirmDelete)
                    goto mainPage;
            }
            else if (userSelectedOption == 11)
            {
                blockTransactions = false;                         // reseting the 
                for (int i = 0; i < transactionsIndex; i++)         //
                {                                                    //
                    transactionsTypes[i] = "";                        //
                    transactions[i] = 0;                               //
                }                                                        // values  ;}
                goto mainPage;         // logging out
            }
            else 
            {
                cout << "\t\t\t\t\t\t\t\t\t\t  Invalid Choice...";   // invalid input
                Sleep(400);
            }   
        }
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tUnexpexted Error Occured......";      /// this will only occur when a really strange error occur :]
        return 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////   main function end    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// main menu
int mainMenu()         
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
///////////////////////////////////////////   end 

////////////////////////////////////////////////////////////////////////////////////// admin functions start ////////////////////////////////////////////////////////////////////////////////////////////////////////////
int managerMenu()
{
    managerHeader();
    int adminSelectedOption;
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Add a New User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. View All Records" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. Add an Asset" << endl; 
    cout << "\t\t\t\t\t\t\t\t\t\t   4. View Bank's Liquidity" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   5. Set Gold Rate" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   6. View Asset's" << endl;   
    cout << "\t\t\t\t\t\t\t\t\t\t   7. Give Loan" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   8. Update Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   9. Reset Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  10. Delete a User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  11. Log Out" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  Please Select an Option...";
    cin >> adminSelectedOption;
    return adminSelectedOption;
}
string resetAdminPassword(string adminPassword, string pass)
{
    string newPass = adminPassword;
    cout << "\n\t\t\t\t\t\t\t\t\tPlease wait processing...";
    Sleep(500);
    if (adminPassword == pass)
    { 
        cout << "\n\t\t\t\t\t\t\t\t\tSet new Password: ";
        newPass = getAnonymousPass();
        cout << "\n\t\t\t\t\t\t\t\t\tPassword Successfully changed\n";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\tIncorrect Password.";
    adminPressAnyKey();
    return newPass;
}
void viewAssets(string bankAssets[], string bankAssetsWorth[], int assetIndex)
{
    for (int i = 0; i < assetIndex; i++)
        cout << "\t\t\t\t\t\t\t\t\t " << setw(8) << bankAssets[i] << "\t\t\t     " << bankAssetsWorth[i] << endl;
}
int addAsset(string bankAssets[], string bankAssetsWorth[], int assetIndex, string newAsset, string assetWorth)
{
    bankAssets[assetIndex] = newAsset;
    bankAssetsWorth[assetIndex] = assetWorth;
    assetIndex++;
    adminPressAnyKey();
    return assetIndex;
}
void adminPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
int liquidity(float userBalances[], int index)
{
    float cashHoldings;
    for (int i = 0; i < index; i++)
        cashHoldings += userBalances[i];
    return cashHoldings;
}
float giveLoan(float userBalances[], int choice)
{
    float loan;
    cout << "\n\t\t\t\t\t\t\t\t\t     Enter the amount of Loan you want to give: ";
    cin >> loan;
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait...";
    Sleep(800);
    float newAmount = userBalances[choice] + loan;
    return newAmount;
}
void modifyInfoAdmin(string userNames[], int index, int &transferIndex)
{
    int choice;
    cout << "\n\t\t\t\t\t\t\t\t\t     Enter the Sr.No you want to change the info of: ";
    cin >> choice;
    
    string newName;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
    cin >> newName;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait...";
    Sleep(800);
    
    if(!userExist(userNames, newName, index, transferIndex))
        userNames[choice] = newName;
}
void viewRecords(string userNames[], string userIDs[], float userBalances[] ,int index ,int del)
{
    for (int i = 0; i < index; i++)
    {
        if (userNames[i] != "")
            cout << "\t\t\t\t\t\t\t\t\t      " << i << "      " << setw(8) << userNames[i] << "\t      " << userIDs[i] << "\t   " << userBalances[i] << endl;
        else   
            continue;
    }
    if (del==0)
    {
        cout << "\n\t\t\t\t\t\t\t\t\tPress any key to continue...";
        getch();
    }
}
void viewRecordHeader()
{
    managerHeader();
    cout << "\t\t\t\t\t\t\t\t\t   #################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t    Sr No\t NAME \t    ID - No. \t Balance($)" << endl;
    cout << "\t\t\t\t\t\t\t\t\t   #################################################" << endl;
    cout << endl;
}
bool addNewUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass)
{
    bool again = false;
    if (uniqueUser(userNames, index, name))
        createUser(userNames, userPasswords, userIDs, index, name, pass);
    else
        cout << "\n\t\t\t\t\t\t\t\t\t\t   User already exists..........";
    int choice = againExecuteThisFunction();  /// if want to execute again
    if (choice == 1)
        again = true;
    return again;
}
int againExecuteThisFunction()
{
    int choice;
    cout << "\n\t\t\t\t\t\t\t\t    Do you want to add another one press 1(yes) or 2(no): ";
    cin >> choice;
    return choice;
}
int setNewGoldRate()
{
    float newGoldRate;
    cout << "\n\n\t\t\t\t\t\t\t\t\tNew Gold Rate: ";
    cin >> newGoldRate;
    return newGoldRate;
}
void deleteUser(string userNames[], int choice)
{
    cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait deleting the records...";
    Sleep(1000);
    
    userNames[choice] = "";  /// just setting name to empty and not displaying it's all records on view record  ;}   
}
////////////////////////////////////////////////////////////////////////////////////// admin functions end ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////// user functions Start ///////////////////////////////////////////////////////////////////////////////////////////////////////////
void userPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();   
}
int userMenu()
{    
    int userOption;
    cout << "\t\t\t\t\t\t\t\t\t\t   1. Check Portfolio" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   2. Deposit Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   3. With-Draw Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   4. Transfer Money To Another Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   5. Invest in Gold" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t   5. Verify Account" << endl;      //// future features "maybe" :}
    // cout << "\t\t\t\t\t\t\t\t\t\t   5. Convert Gold" << endl;        //// future features "maybe" :}
    cout << "\t\t\t\t\t\t\t\t\t\t   6. View Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   7. Block/Unblock Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   8. Change Name" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   9. Change Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  10. Delete Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  11. Log Out" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  Please Select an Option...";
    cin >> userOption;
    return userOption;
}
void greetUser(string userName)
{
    cout << "\t\t\t\t\t\t\t\t\t\t   Welcome Back " << userName << endl;
}
void checkPortfolio(float userInvestments[], float userBalances[], int currentIndex, float goldRate)
{
    cout << "\t\t\t\t\t\t\t\t\t\tCash: $" << userBalances[currentIndex] << endl;
    if (userInvestments[currentIndex] != 0)
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tGold(in grams): " << userInvestments[currentIndex];
        cout << "\n\t\t\t\t\t\t\t\t\t\tGold(in Dollars): " << userInvestments[currentIndex] * goldRate << endl;
    }
}
void depositMoney(float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex, bool blockTransactions)
{
    userHeader();
    if (!blockTransactions)
    {
        float deposit;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Deposit: $";
        cin >> deposit;

        userBalances[currentIndex] += deposit;

        cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
        Sleep(1000);

        cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully deposited \"$" << deposit << "\" into you're account." << endl;
        cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
        
        //// storing the transaction history
        transactions[transactionsIndex] = deposit;
        transactionsTypes[transactionsIndex] = "Deposit";
        transactionsIndex++;
    }
    else
        cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;

    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
void withdrawMoney(float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex, bool blockTransactions)
{
    userHeader();
    if (!blockTransactions)
    {
        cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalances[currentIndex] << endl << endl;

        float withdraw;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to With-Draw: $";
        cin >> withdraw;

        cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
        Sleep(1000);

        if (withdraw <= userBalances[currentIndex])
        {
            userBalances[currentIndex] -= withdraw;
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully With-Drawn \"$" << withdraw << "\" from you're account." << endl;
            cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
            
            //// storing the transaction history
            transactions[transactionsIndex] = withdraw;
            transactionsTypes[transactionsIndex] = "Withdraw";
            transactionsIndex++;
        }
        else if (withdraw > userBalances[currentIndex]) 
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
        else
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn error occured." << endl;          /// any error case
    }
    else
        cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
void transferMoney(string userNames[], float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex,int &transferIndex, bool blockTransactions, int index)
{
    userHeader();
    if (!blockTransactions)
    {
        cout << "\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalances[currentIndex] << endl << endl;

        float transfer;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Transfer: $";
        cin >> transfer;

        string name;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter name of the reciever: ";
        cin >> name;

        cout << "\n\t\t\t\t\t\t\t\t\t\tPlease wait while you're transaction is in process";
        Sleep(1000);

        bool recieverExists = userExist(userNames, name, index, transferIndex);
        if (recieverExists)
        {
            if (transfer <= userBalances[currentIndex])
            {                                                       //// transfered
                userBalances[currentIndex] -= transfer;               //  from user1
                userBalances[transferIndex] += transfer;              //   to user2

                cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully Transfered \"$" << transfer << "\" from you're account to the account of \"" << userNames[transferIndex] << "\"" << endl;
                cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
                
                //// storing the transaction history
                transactions[transactionsIndex] = transfer;
                transactionsTypes[transactionsIndex] = "Transfer";
                transactionsIndex++;
            }
            else if (transfer > userBalances[currentIndex]) 
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
            else
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn error occured." << endl;          /// any error case
        }
        else
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tNo such user exists in our database ;(" << endl;
    }
    else
        cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
void investGold(string userNames[],float userInvestments[], float userBalances[], float transactions[], string transactionsTypes[], int currentIndex,  int &transactionsIndex, bool blockTransactions, int index, float goldRate)
{
    userHeader();
    if (!blockTransactions)
    {
        cout << "\t\t\t\t\t\t\t\t\t\tYour Balance: $" << userBalances[currentIndex] << endl << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t1-Gram of Gold = $" << goldRate << endl  << endl;
        
        float investment;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter amount you want to invest in Gold: $";
        cin >> investment;

        float goldinGrams = investment / goldRate;
        cout << "\n\t\t\t\t\t\t\t\t\t\tYou will get " << goldinGrams << "-Gram of Gold.";
again: //// in case of in valid input start again and ask for correct input
        int proceed;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want to proceed Press 1(yes) or 2(no)... ";
        cin >> proceed;
        if (proceed == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
            Sleep(1000);
            if (investment <= userBalances[currentIndex] )
            {
                userBalances[currentIndex] -= investment;
                userInvestments[currentIndex] += goldinGrams;
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou have successfully invested \"$" << investment << "\" into " << goldinGrams << "-Gram of gold..";
                cout << "\n\t\t\t\t\t\t\t\t\t\tNew Balance: " << userBalances[currentIndex] << endl;

                //// storing the transaction history
                transactions[transactionsIndex] = investment;
                transactionsTypes[transactionsIndex] = "Investment";
                transactionsIndex++;
            }
            else if (investment > userBalances[currentIndex])
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tBalance is Low.";
            else
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tAn Error occured.. :/";
        }
        else if (proceed == 2)
            cout << "\n\t\t\t\t\t\t\t\t\t\tTransaction Terminated.........";
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tInvalid input.";
            goto again;                /// invalid input case
        }
    }
    else
        cout << "\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
void viewTransactions(string transactionsTypes[], float transactions[], int transactionsIndex)
{
    userHeader();
    if (transactions[0] != 0)
    {
        cout << "\t\t\t\t\t\t\t\t       #################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t\t  Transaction Type\t     Amount($)" << endl;
        cout << "\t\t\t\t\t\t\t\t       #################################################" << endl << endl;
        for (int i = 0; i < transactionsIndex; i++ )
        {
            cout << "\t\t\t\t\t\t\t\t\t     " << transactionsTypes[i] << "\t\t\t" << transactions[i] << endl;
        }
    }
    else
        cout << "\n\t\t\t\t\t\t\t\t\t\tNo Transactions for Now..";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
bool blockOrUnblockTransactions(bool blockTransactions)
{
    bool transactionStatus = blockTransactions;
    cout << "\t\t\t\t\t\t\t\t\t\tPlease wait...";
    Sleep(1000);
    if (transactionStatus == false)         
        transactionStatus = true;           // false ---> true
    else
        transactionStatus = false;        // true  ---> false
    return transactionStatus;
}
void modifyInformation(string userNames[], string userPasswords[], int currentIndex, int index, int &transferIndex)
{
    userHeader();   
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    currentPass =  getAnonymousPass();
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    Sleep(1000);
    
    if(currentPass == userPasswords[currentIndex])
    {
        string newName;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
        cin >> newName;

        cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
        Sleep(1000);
        if(!userExist(userNames,newName, index, transferIndex))                    /// does'nt exist
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
}
void changePassword(string userPasswords[], int currentIndex)
{
    userHeader();
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter Current Password: ";
    currentPass = getAnonymousPass();
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    Sleep(1000);
    
    if(currentPass == userPasswords[currentIndex])
    {
        string newPass;
        cout << "\n\t\t\t\t\t\t\t\t\t\tSet New Password: ";
        newPass = getAnonymousPass();
        userPasswords[currentIndex] = newPass;
        cout << "\n\t\t\t\t\t\t\t\t\t\tPassword Successfully changed..";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
bool deleteAccount(string userNames[], string userPasswords[],int currentIndex)
{
    bool accountDeletion = false;
    userHeader();
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    currentPass = getAnonymousPass();
    
    cout << "\n\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    Sleep(1000);
    
    if(currentPass == userPasswords[currentIndex])
    {
        userNames[currentIndex] = "";         /// deleting name so can't access this account now     ;}
        
        accountDeletion = true;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tYour account has been removed.";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    return accountDeletion;
}
////////////////////////////////////////////////////////////////////////////////////////// user  functions  End  ////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////// input validation start //////////////////////////////////////////////////////////////////////////////////////////////////////////
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
bool checkUserValidity(string userNames[], string userPasswords[], int index, int &currentIndex,  string name, string pass)
{
    bool validPass = false;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i] && pass == userPasswords[i])
        {
            validPass = true;
            currentIndex = i;
            break;
        }    
    }
    return validPass;
}
bool userExist(string userNames[], string name, int index, int &transferIndex)
{
    bool exists = false;
    for (int i = 0; i < index; i++)
    {
        if (name == userNames[i])
        {
            exists = true;    
            transferIndex = i;       // for transfer of cash  
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
///////////////////////////////////////////////////////////////////////////////////////// input validation end  //////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////// start of signUp/signIn //////////////////////////////////////////////////////////////////////////////////////////////////////////
string getAnonymousPass()
{
    char singleLetter;
    string completeWord;
    while(true)
    {
        singleLetter = getch();
        if (singleLetter == '\r')
            break;
        cout << "*";
        completeWord += singleLetter;
    }
    return completeWord;
}
void signUpCheck()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Please wait Creating new user....";
    Sleep(1000);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t   User already exists" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t   Press any key to continue....";
    getch();
}
bool adminLoginCheck(string pass, string &adminPassword)
{
    bool login = false; 
    if (pass == adminPassword)
        login = true;
    return login;
}
void createUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass)
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t   Please wait Creating new user....";
    Sleep(1000);
    /// assigning values
    userNames[index] = name;
    userPasswords[index] = pass;
    userIDs[index] = "000"; 
    userIDs[index] += to_string(index+1);
    index++;  
    cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t   Successfully created new user" << endl;
}
/////////////////////////////////////////////////////////////////////////////////////// end of signUp/SignIn /////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////   headers   start    //////////////////////////////////////////////////////////////////////////////////////////////////////////////   
void header()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    system("cls");
    cout << R"(                                                                         ______                                                    )" << endl;
    cout << R"(                                                                        /\  _  \                                                   )" << endl;
    cout << R"(                                                                        \ \ \L\ \    ____     __  __    _ __      __               )" << endl;
    cout << R"(                                                                         \ \  __ \  /\_ ,`\  /\ \/\ \  /\`'__\  /'__`\             )" << endl;
    cout << R"(                                                                          \ \ \/\ \ \/_/  /_ \ \ \_\ \ \ \ \/  /\  __/             )" << endl;
    cout << R"(                                                                           \ \_\ \_\  /\____\ \ \_____\ \ \_\  \ \____\            )" << endl;
    cout << R"(                                                                            \/_/\/_/  \/____/  \/______\ \/_/   \/____/            )" << endl;
    cout << R"(                                                                                                                                   )" << endl;
    cout << R"(                                                                                                                                   )" << endl;
    cout << R"(                                                               ____                     __           ______                        )" << endl;
    cout << R"(                                                              /\  _`\                  /\ \         /\__  _\                       )" << endl;
    cout << R"(                                                              \ \ \L\ \     __      ___\ \ \/'\     \/_/\ \/     ___     ___       )" << endl;
    cout << R"(                                                               \ \  _ <'  /'__`\  /' _ `\ \ , <        \ \ \   /' _ `\  /'___\     )" << endl;
    cout << R"(                                                                \ \ \L\ \/\ \L\.\_/\ \/\ \ \ \\`\       \_\ \__/\ \/\ \/\ \__/  __ )" << endl;
    cout << R"(                                                                 \ \____/\ \__/.\_\ \_\ \_\ \_\ \_\     /\_____\ \_\ \_\ \____\/\_\)" << endl;
    cout << R"(                                                                  \/___/  \/__/\/_/\/_/\/_/\/_/\/_/     \/_____/\/_/\/_/\/____/\/_/)" << endl;
    cout << endl;
    cout << "                                                                  ####################################################################" << endl; 
    cout << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void signInHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void signUpHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void adminLoginHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void userHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void managerHeader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//////////////////////////////////////////////////////////////////////////////////////   headers   end    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////// End of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////