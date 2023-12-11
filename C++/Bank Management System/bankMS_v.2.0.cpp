////////////////////////////////////////////////////////////////////////////////////////// Start of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>                  // for input and output
#include <typeinfo>                // for checking the type of variable
#include <string>                // for string functions
#include <windows.h>           // for color
#include <iomanip>           // for setw()
#include <conio.h>         // for getch()
#include <fstream>       // for file handling
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
int addAsset(string [], string [],int, string, string);
int liquidity(float [], int );
int setNewGoldRate();
bool addNewUser(string [], string [], string [], int &, string, string);
bool modifyInfoAdmin(string [], int , int &);
bool deleteUser(string [], string [], float [], int , int &);
void viewRecords(string [], string [], float [] ,int  ,int);
void viewAssets(string [], string [], int);
string resetAdminPassword(string, string);
float giveLoan(float [],int );
//////////////////////// user
void greetUser(string);   
/// user functions
bool blockOrUnblockTransactions(bool);
bool modifyInformation(string [], string [], int , int , int &, string);
bool deleteAccount(string [], string [],int , int &, float [], float [], string []);
bool changePassword(string [], int , string);
bool depositMoney(float [], int , float );
bool withdrawMoney(float [], int , float );
bool transferMoney(string [], float [], int , int &, int , float , string );
bool investGold(string [],float [], float [], int , int , float , float );
void viewTransactions(string [], float [], int );
void checkPortfolio(float [], float [], int , float );
/// menus
string mainMenu();
string managerMenu();
string userMenu();
/// sign up
void createUser(string [], string [], string [], int &, string , string );
/// data Verification
bool uniqueUser(string[], int &, string);   /// sign up
bool userExist(string[], string, int, int &);     /// sign in
bool checkUserValidity(string [], string [], int , int &, string, string);  /// pass checker
///// error handling
void accountNotExists();
void passNotCorrect();
/////////////////  Extra   /////////////////////////// 
string getAnonymousPass();
string againExecuteThisFunction();
void showBalance(float [], int );
void transactionError();
void goldHeader(float);
void viewRecordHeader();
void viewTransactionsHeader();
void adminPressAnyKey();
void userPressAnyKey();
void mainPressAnyKey();
void simulateProcessing();
void simulateWithoutTelling();
void storeTransactionHistory(string [], float [], int &, float );
void invest(float [], float [], int , float , float );
void transferNow(string [], float [], int , int , float );
void loader();
bool nameCheck(string);
void simulateWithoutTellingLONG();
void invalidNameError();
/// data storage and retrival
void storeDataLocally(string [], string [], string [], float [], float [], string [], float [], int );
void loadData(string [], string [], string [], float [], float [], int &);
string getFieldData(string , int );
///////////////////////////////////////////////////////////////////////////////
// xtra
string getAdminPass();
void accessDeniedError();
string getUserEnteredName();
string getNAME();
void userAlreadyExists();
void terminateProgram();
void invalidChoiceError();


////////////////////////////////
/// colors
string setcolor(unsigned short );
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
//////////////////////////////////////////////////////////////////////////////////////   main function start    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    //// arrays for user data
    int index = 0;                                                   /// counter for the storing values
    string userNames[100];
    string userPasswords[100];
    string userIDs[100];
    float userBalances[100] = {0};
    float userInvestments[100] = {0};
    float transactions[100] = {0};           
    string transactionsTypes[100];
    ///// loading the data
    loadData(userNames, userPasswords, userIDs, userBalances, userInvestments, index);   /// loading data from file
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
    string choice = "0";
    string LogInTo = "none"; 
    // loader(); 
mainPage:       ///// for logging out of user's
    while(choice != "4")
    {
        choice = mainMenu();         //// menu bar option select
        if (choice == "1")             /// admin login
        { 
            adminLoginHeader();
            string userEnterAdminPass = getAdminPass();
            bool login =  adminLoginCheck(userEnterAdminPass, adminPassword);
            simulateProcessing();
            if (login)
            {
                LogInTo = "admin";
                break;
            }
            accessDeniedError();
            mainPressAnyKey();
        }
        else if (choice == "2")      /////sig in user
        {
            string userEnteredPassword, userEnteredName = getUserEnteredName();
            setcolor(lightcyan);
            cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your Password: ";
            userEnteredPassword = getAnonymousPass();
            simulateProcessing();
            if (userExist(userNames, userEnteredName, index, transferIndex))
            {
                if (checkUserValidity(userNames, userPasswords, index, currentIndex, userEnteredName, userEnteredPassword))     /// password and name checking
                {
                    LogInTo = "user";       /// login successful
                    break;
                }
                passNotCorrect();  // no need to place in else   :)
            }
            else
                accountNotExists();
            setcolor(white);
        }
        else if (choice == "3")   //// sign up user
        {
            string name = getNAME();
            string pass;
            cout << "\t\t\t\t\t\t\t\t\t\t\tSet password: ";
            pass = getAnonymousPass();
            setcolor(lightblue);
            if (uniqueUser(userNames, index ,name))         /// User created
                createUser(userNames, userPasswords, userIDs, index, name, pass);
            else
                userAlreadyExists();
            setcolor(white);
            mainPressAnyKey();
        }
        else if (choice == "4")
        {
            terminateProgram();
            storeDataLocally(userNames, userPasswords, userIDs, userBalances, userInvestments, transactionsTypes, transactions, index);
            return 0;                         /// end program
        }
        else             /// for error cases
            invalidChoiceError();
    }
    if (LogInTo == "admin")
    {
        string adminSelectedOption = "0";
        while(adminSelectedOption != "11")
        { 
            adminSelectedOption = managerMenu();
            if (adminSelectedOption == "1")
            {
                bool addUserAgain = true;
                while (addUserAgain)        /// loop is for the admin if he want to add more then "1" user
                {
retakeNameInputAdminSignUp:   // if invalid name then again
                    managerHeader();
                    string newUserName, newUserPass;
                    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the Name: ";
                    cin >> newUserName;
                    bool nameValidation = nameCheck(newUserName);
                    if (!nameValidation)
                    {
                        invalidNameError();
                        goto retakeNameInputAdminSignUp;
                    }
                    cout << "\t\t\t\t\t\t\t\t\t\t\tSet Password: ";
                    newUserPass =  getAnonymousPass();
                    addUserAgain = addNewUser(userNames, userPasswords, userIDs, index, newUserName, newUserPass);
                }
            }
            else if (adminSelectedOption == "2")
            {
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances ,index , del);      
            }
            else if (adminSelectedOption == "3")
            {   
                managerHeader();
                string assetName;
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the assest's name you want to add: ";
                cin >> assetName;
                string assetWorth;
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the assest's worth you have added in (***k) format: ";
                cin >> assetWorth;
                assetIndex = addAsset(bankAssets, bankAssetsWorth, assetIndex, assetName, assetWorth);  // increasing the asset index by value return
            }
            else if (adminSelectedOption == "4")
            {   
                managerHeader();
                int cashHoldings = liquidity(userBalances, index);
                cout << "\t\t\t\t\t\t\t\t\t\t\tTotal Cash available in Liquid: " << cashHoldings << endl;
                adminPressAnyKey();
            }
            else if (adminSelectedOption == "5")
            {   
                managerHeader();
                goldHeader(goldRate);
                goldRate = setNewGoldRate();       
                adminPressAnyKey();
            }
            else if (adminSelectedOption == "6")
            {   
                managerHeader();
                cout << "\t\t\t\t\t\t\t\t\t\t\tAsset's Name\t\t\tAsset's Worth($)\n";
                viewAssets(bankAssets, bankAssetsWorth, assetIndex);
                adminPressAnyKey();
            }
            else if (adminSelectedOption == "7")
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                int loanIndex;
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to give loan to: ";
                cin >> loanIndex;
                userBalances[loanIndex] = giveLoan(userBalances, loanIndex);
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == "8")
            {   
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                bool modification = modifyInfoAdmin(userNames, index, transferIndex);
                if (modification == true)
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tModification was successful";
                else
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tModification was not successful";
                del = 0;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
            }
            else if (adminSelectedOption == "9")
            {   
                managerHeader();
                string userEnteredAdminpass;
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your current Password: ";
                userEnteredAdminpass = getAnonymousPass();
                adminPassword = resetAdminPassword(adminPassword, userEnteredAdminpass);
            }
            else if (adminSelectedOption == "10")
            {   
            Again:         // if invalid choice then again
                del = 1;
                viewRecordHeader();
                viewRecords(userNames, userIDs, userBalances , index, del);
                int deletionIndex;
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to remove: ";
                cin >> deletionIndex;
                if (deletionIndex >= index || deletionIndex < 0)
                {
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tInvalid Sr.No";
                    simulateWithoutTelling();
                    goto Again;
                }                
                else
                {
                    bool deletion = deleteUser(userNames, userPasswords, userBalances, deletionIndex, index);
                    if (deletion)
                        cout << "\n\t\t\t\t\t\t\t\t\t\t\tThe record was deleted successfully";
                    else
                        cout << "\n\t\t\t\t\t\t\t\t\t\t\tThe record was not deleted";
                    del = 0;
                    viewRecordHeader();
                    viewRecords(userNames, userIDs, userBalances , index, del);
                }
            }
            else if (adminSelectedOption == "11")
            {
                goto mainPage;     /// logging out
            }
            else
            {
                setcolor(lightred);
                cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Choice...";      /// invalid input
                setcolor(white);
                simulateWithoutTelling();
            }
        }
    }
    else if (LogInTo == "user")
    {
        string userSelectedOption = "0";
        while(userSelectedOption != "11")
        {
            userHeader();
            greetUser(userNames[currentIndex]);
            cout << endl;
            userSelectedOption = userMenu();
            if (userSelectedOption == "1")
            {
                userHeader();
                checkPortfolio(userInvestments, userBalances, currentIndex, goldRate);
                userPressAnyKey();
            }
            else if(userSelectedOption == "2")
            {
retakeDepositInput:  // if invalid input then again
                userHeader();
                string deposit;
                if (!blockTransactions)
                {
                    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Deposit: $";
                    cin >> deposit;
                    try
                    {
                        float temp = stof(deposit);       /// temp storing the value to check if it is float or not
                    }
                    catch(invalid_argument)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Input...";
                        simulateWithoutTellingLONG();
                        goto retakeDepositInput;
                    }
                    bool depositStatus = depositMoney(userBalances, currentIndex, stof(deposit));
                    if (depositStatus == true)   // transaction successful then storeDataLocally the history
                        storeTransactionHistory(transactionsTypes, transactions, transactionsIndex, stof(deposit));
                    else
                        transactionError();
                }
                else
                    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
                userPressAnyKey();
            }
            else if (userSelectedOption == "3")
            {
retakeWithdrawInput:  // if invalid input then again
                userHeader();
                string withdraw;
                if (!blockTransactions)
                {
                    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Balance is: $" << userBalances[currentIndex] << endl << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to With-Draw: $";
                    cin >> withdraw;
                    try
                    {
                        float temp = stof(withdraw);       /// temp storing the value to check if it is float or not
                    }
                    catch(invalid_argument)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Input...";
                        simulateWithoutTellingLONG();
                        goto retakeWithdrawInput;
                    }
                    bool withdrawStatus = withdrawMoney(userBalances, currentIndex, stof(withdraw));
                    if (withdrawStatus)
                        storeTransactionHistory(transactionsTypes, transactions, transactionsIndex, stof(withdraw));
                }
                else
                    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
                userPressAnyKey();
            }
            else if (userSelectedOption == "4")
            {
retakeTransferInput:  // if invalid input then again
                userHeader();
                string transfer;
                if (!blockTransactions)
                {
                    showBalance(userBalances, currentIndex);
                    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the amount that you want to Transfer: $";
                    cin >> transfer;
                    try
                    {
                        float temp = stof(transfer);       /// temp storing the value to check if it is float or not
                    }
                    catch(invalid_argument)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Input...";
                        simulateWithoutTellingLONG();
                        goto retakeTransferInput;
                    }
                    if (stof(transfer) > 0)
                    {
                        string receiverName;
                        cout << "\t\t\t\t\t\t\t\t\t\t\tEnter name of the reciever: ";
                        cin >> receiverName;
                        bool transferStatus = transferMoney(userNames, userBalances, currentIndex, transferIndex, index, stof(transfer), receiverName);            
                        if (transferStatus)
                            storeTransactionHistory(transactionsTypes, transactions, transactionsIndex,stof(transfer));
                    }
                    else
                        transactionError();
                }
                else
                    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
                userPressAnyKey();
            }
            else if (userSelectedOption == "5")
            {
                userHeader();
                float investment;
                if (!blockTransactions)
                {
                    showBalance(userBalances, currentIndex);
                    goldHeader(goldRate);
                    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter amount you want to invest in Gold: $";
                    cin >> investment;
                    if (investment > 0)
                    {
                        bool investmentStatus = investGold(userNames, userInvestments, userBalances, currentIndex, index, goldRate, investment);             
                        if (investmentStatus)
                            storeTransactionHistory(transactionsTypes, transactions, transactionsIndex, investment);
                    }
                    else
                        transactionError();
                }   
                else
                    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Transactions are Blocked..." << endl;
                userPressAnyKey();
            }
            else if (userSelectedOption == "6")
            {
                userHeader();
                if (transactions[0] != 0)
                {
                    viewTransactionsHeader();
                    viewTransactions(transactionsTypes, transactions, transactionsIndex);
                }
                else
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tNo Transactions for Now..";
                userPressAnyKey();
            }
            else if (userSelectedOption == "7")
            {
                userHeader();
                blockTransactions = blockOrUnblockTransactions(blockTransactions);
                if(blockTransactions == true)
                    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour Transactions have been Blocked.";
                else
                    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour Transactions have been Unblocked.";
                userPressAnyKey();
            }
            else if (userSelectedOption == "8")
            {
                userHeader();   
                string userCurrentPassword;
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
                userCurrentPassword =  getAnonymousPass();
                bool modified = modifyInformation(userNames, userPasswords, currentIndex, index, transferIndex, userCurrentPassword);
                if (modified)
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tName modified Successfully";
                else
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tName was not modified Successfully";
                userPressAnyKey();
            }
            else if (userSelectedOption == "9")
            {
                userHeader();
                string userEnteredPassword;
                cout << "\t\t\t\t\t\t\t\t\t\t\tEnter Current Password: ";
                userEnteredPassword = getAnonymousPass();
                bool modificationOfPassword = changePassword(userPasswords, currentIndex, userEnteredPassword);
                if (modificationOfPassword)
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPassword was changed successfully";
                else
                    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPassword was not changed";
                userPressAnyKey();
            }
            else if (userSelectedOption == "10")
            {
                bool confirmDelete = deleteAccount(userNames, userPasswords, currentIndex, index, userBalances, userInvestments, userIDs);
                if (confirmDelete)
                    goto mainPage;
            }
            else if (userSelectedOption == "11")
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
                setcolor(lightred);
                cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Choice...";   // invalid input
                setcolor(white);
                simulateWithoutTelling();
            }   
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////   main function end    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// main menu
string mainMenu()         
{
    header();
    string option;
    setcolor(cyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. Login as Manager" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. Login as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. Sign up as User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. End" << endl;
    cout << endl;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPlease Select an Option...";
    setcolor(white);
    cin >> option;
    return option;
}
void mainPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue..";
    getch();
}   
////////////////////////////////////////////////////////////////////////////////////// admin functions start ////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loadData(string userNames[], string userPasswords[], string userIDs[], float userBalances[], float userInvestments[], int &index)
{
    try
    {
        fstream loadFile;
        string data = "";
        loadFile.open("data.txt", ios::in);
        bool firstIteration = true;
        while (!loadFile.eof())
        {
            getline(loadFile, data);
            if (firstIteration)
            {
                firstIteration = false;
                continue;
            }
            userNames[index] = getFieldData(data, 0);
            userPasswords[index] = getFieldData(data, 1);
            userIDs[index] = getFieldData(data, 2);
            userBalances[index] = stof(getFieldData(data, 3));
            userInvestments[index] = stof(getFieldData(data, 4));
            index++;
        }
        loadFile.close();
    }
    catch(std::invalid_argument)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "\033[1m";
        cout << "\033[31m";
        remove("data.txt");     /// removing the file as it is corrupted
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tData file is corrupted.";
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tCreating new record file"; 
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tDo you want to proceed.";
        userPressAnyKey();
        cout << "\033[0m";
        cout << "\033[0m";
    }
}
string getFieldData(string data, int count)
{
    string result = "";
    int comma = 0;
    for (int i =0; i<data.length(); i++)
    {
        if (data[i] == ',')
            comma++;
        else if (comma == count)
            result += data[i];
        else if (comma > count)
            break;
    }
    return result;
}
void storeDataLocally(string userNames[], string userPasswords[], string userIDs[], float userBalances[], float userInvestments[], string transactionsTypes[], float transactions[], int index)
{
    fstream storeFile;
    string data = "";
    storeFile.open("data.txt", ios::out);
    storeFile << "Name,Password,ID,Balance,Investments\n";
    for (int i = 0; i < index; i++)
    {
        if (i == index - 1)     // last line not adding "\n"
            data += userNames[i] + "," + userPasswords[i] + "," + userIDs[i] + "," + to_string(userBalances[i]) + "," + to_string(userInvestments[i]);
        else    
            data += userNames[i] + "," + userPasswords[i] + "," + userIDs[i] + "," + to_string(userBalances[i]) + "," + to_string(userInvestments[i]) + "\n";
        storeFile << data;
        data = "";        
    }
    storeFile.close();
}
string managerMenu()
{
    managerHeader();
    string adminSelectedOption;
    setcolor(cyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. Add a New User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. View All Records" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. Add an Asset" << endl; 
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. View Bank's Liquidity" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t5. Set Gold Rate" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t6. View Asset's" << endl;   
    cout << "\t\t\t\t\t\t\t\t\t\t\t7. Give Loan" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t8. Update Information" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t9. Reset Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t10. Delete a User" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t11. Log Out" << endl;
    cout << endl;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPlease Select an Option...";
    cin >> adminSelectedOption;
    setcolor(white);
    return adminSelectedOption;
}
string resetAdminPassword(string adminPassword, string pass)
{
    string newPass = adminPassword;
    simulateProcessing();
    if (adminPassword == pass)
    { 
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tSet new Password: ";
        newPass = getAnonymousPass();
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tPassword Successfully changed\n";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tIncorrect Password.";
    adminPressAnyKey();
    return newPass;
}
void viewAssets(string bankAssets[], string bankAssetsWorth[], int assetIndex)
{
    for (int i = 0; i < assetIndex; i++)
        cout << "\t\t\t\t\t\t\t\t\t\t\t" << setw(8) << bankAssets[i] << "\t\t\t     " << bankAssetsWorth[i] << endl;
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
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
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
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter the amount of Loan you want to give: ";
    cin >> loan;
    simulateProcessing();
    float newAmount = userBalances[choice] + loan;
    return newAmount;
}
bool modifyInfoAdmin(string userNames[], int index, int &transferIndex)
{
    bool modification = false;
    int choice;
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter the Sr.No you want to change the info of: ";
    cin >> choice;
    string newName;
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
    cin >> newName;
    bool nameValidation = nameCheck(newName);
    if (!nameValidation)
    {
        invalidNameError();
        return modification;
    }
    simulateProcessing();
    if(!userExist(userNames, newName, index, transferIndex))
    {
        userNames[choice] = newName;
        modification = true;
    }
    return modification;
}
void viewRecords(string userNames[], string userIDs[], float userBalances[] ,int index ,int del)
{
    for (int i = 0; i < index; i++)
        cout << "\t\t\t\t\t\t\t\t\t\t\t " << i << "      " << setw(8) << userNames[i] << "\t      " << userIDs[i] << "\t   " << userBalances[i] << endl;
    if (del==0)
        adminPressAnyKey();
}
void viewRecordHeader()
{
    managerHeader();
    cout << "\t\t\t\t\t\t\t\t\t\t\t#################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t Sr No\t NAME \t    ID - No. \t Balance($)" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t#################################################" << endl;
    cout << endl;
}
bool addNewUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass)
{
    bool again = false;
    if (uniqueUser(userNames, index, name))
        createUser(userNames, userPasswords, userIDs, index, name, pass);
    else
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tUser already exists..........";
choiceAgain:  // if invalid choice then again
    string choice = againExecuteThisFunction();  /// if want to execute again
    if (choice == "1")
        again = true;
    else if (choice == "2")
        again = false;
    else
    {
        cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Choice..........";
        simulateWithoutTelling();
        goto choiceAgain;   // choice not correct so again
    }
    return again;
}
int setNewGoldRate()
{
    float newGoldRate;
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tNew Gold Rate: ";
    cin >> newGoldRate;
    return newGoldRate;
}
bool deleteUser(string userNames[], string userPasswords[], float userBalances[], int choice, int &userCount)
{
    simulateProcessing();
    for (int i = choice; i < userCount; i++)
    {
        userNames[i] = userNames[i+1];
        userPasswords[i] = userPasswords[i+1];
        userBalances[i] = userBalances[i+1];
    }
    userCount--;
    return true;
}
string againExecuteThisFunction()
{
    string choice;
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tDo you want to add another one press 1(yes) or 2(no): ";
    cin >> choice;
    return choice;
}
////////////////////////////////////////////////////////////////////////////////////// admin functions end ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////// user functions Start ///////////////////////////////////////////////////////////////////////////////////////////////////////////
string userMenu()
{    
    string userOption;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. Check Portfolio" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. Deposit Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. With-Draw Money" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. Transfer Money To Another Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t5. Invest in Gold" << endl;
    // cout << "\t\t\t\t\t\t\t\t\t\t\t5. Verify Account" << endl;      //// future features "maybe" :}
    // cout << "\t\t\t\t\t\t\t\t\t\t\t5. Convert Gold" << endl;        //// future features "maybe" :}
    cout << "\t\t\t\t\t\t\t\t\t\t\t6. View Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t7. Block/Unblock Transaction's" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t8. Change Name" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t9. Change Password" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t10. Delete Account" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t11. Log Out" << endl;
    cout << endl;
    setcolor(yellow);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPlease Select an Option...";
    cin >> userOption;
    setcolor(white);
    return userOption;
}
void userPressAnyKey()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();   
}
void greetUser(string userName)
{
    setcolor(cyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\tWelcome Back " << userName << endl;
    setcolor(white);
}
void checkPortfolio(float userInvestments[], float userBalances[], int currentIndex, float goldRate)
{
    cout << "\t\t\t\t\t\t\t\t\t\t\tCash: $" << userBalances[currentIndex] << endl;
    if (userInvestments[currentIndex] != 0)
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tGold(in grams): " << userInvestments[currentIndex];
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tGold(in Dollars): " << userInvestments[currentIndex] * goldRate << endl;
    }
}
bool depositMoney(float userBalances[], int currentIndex, float deposit)
{
    bool status = false;
    simulateProcessing();
    if (deposit > 0)
    {
        userBalances[currentIndex] += deposit;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully deposited \"$" << deposit << "\" into you're account." << endl;
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
        status = true;
    }
    return status;
}
void storeTransactionHistory(string transactionsTypes[], float transactions[], int &transactionsIndex, float deposit)
{
    transactions[transactionsIndex] = deposit;
    transactionsTypes[transactionsIndex] = "Deposit";
    transactionsIndex++;
}
bool withdrawMoney(float userBalances[], int currentIndex, float withdraw)
{
    bool status = false;
    simulateProcessing();
    if (withdraw <= userBalances[currentIndex] && withdraw > 0)
    {
        userBalances[currentIndex] -= withdraw;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully With-Drawn \"$" << withdraw << "\" from you're account." << endl;
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
        status = true;
    }
    else if (withdraw > userBalances[currentIndex]) 
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
    return status;
}
bool transferMoney(string userNames[], float userBalances[], int currentIndex, int &transferIndex, int index, float transfer, string name)
{
    bool status = false;
    simulateProcessing();
    bool recieverExists = userExist(userNames, name, index, transferIndex);
    if (recieverExists)
    {
        if (transfer <= userBalances[currentIndex] && transfer > 0)
        {
            transferNow(userNames, userBalances, currentIndex, transferIndex, transfer);
            status = true;
        }
        else if (transfer > userBalances[currentIndex]) 
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou're Balance is low." << endl;
        else
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tThe attempted transaction was not approved.\n";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tNo such user exists in our database ;(" << endl;
    return status;
}
bool investGold(string userNames[],float userInvestments[], float userBalances[], int currentIndex, int index, float goldRate, float investment)
{
    bool status = false;
    float goldinGrams = investment / goldRate;
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tYou will get " << goldinGrams << "-Gram of Gold.";
    string proceed;
    while(proceed != "2")
    {
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tDo you want to proceed Press 1(yes) or 2(no)... ";
        cin >> proceed;
        if (proceed == "1")
        {
            simulateProcessing();
            if (investment <= userBalances[currentIndex])
            {
                invest(userBalances, userInvestments, currentIndex, investment, goldinGrams);
                break;
            }
            else if (investment > userBalances[currentIndex])
            {
                cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tBalance is Low.";
                break;
            }
        }
        else if (proceed == "2")
            cout << "\n\t\t\t\t\t\t\t\t\t\t\tTransaction Terminated.........";
        }
    return status;
}
void viewTransactions(string transactionsTypes[], float transactions[], int transactionsIndex)
{
    for (int i = 0; i < transactionsIndex; i++ )
        cout << "\t\t\t\t\t\t\t\t\t\t\t" << transactionsTypes[i] << "\t\t\t" << transactions[i] << endl;
}
bool blockOrUnblockTransactions(bool blockTransactions)
{
    bool transactionStatus = blockTransactions;
    simulateProcessing();
    if (transactionStatus == false)         
        transactionStatus = true;           // false ---> true
    else
        transactionStatus = false;        // true  ---> false
    return transactionStatus;
}
bool modifyInformation(string userNames[], string userPasswords[], int currentIndex, int index, int &transferIndex, string currentPass)
{
    bool modified = false;
    simulateProcessing();
    if(currentPass == userPasswords[currentIndex])
    {
        string newName;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tEnter new Name: ";
        cin >> newName;
        bool nameValidation = nameCheck(newName);
        if (!nameValidation)
        {
            invalidNameError();
            return false;    // going back to the menu
        }
        simulateProcessing();
        if(!userExist(userNames,newName, index, transferIndex))                    /// does'nt exist
        {
            string oldName = userNames[currentIndex];         //// optional for output :]
            userNames[currentIndex] = newName;
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou're name was successfully changed from \"" << oldName << "\" to " << "\"" << newName << "\"\n";
            modified = true;
        }
        else
            cout << "\n\t\t\t\t\t\t\t\t\t\t\tUser Already Exists..\n";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tInvalid Password.\n";
    return modified;
}
bool changePassword(string userPasswords[], int currentIndex, string currentPass)
{
    bool passwordModification = false;
    simulateProcessing();
    if(currentPass == userPasswords[currentIndex])
    {
        string newPass;
        cout << "\n\t\t\t\t\t\t\t\t\t\t\tSet New Password: ";
        newPass = getAnonymousPass();
        userPasswords[currentIndex] = newPass;
        passwordModification = true;
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    return passwordModification;
}
bool deleteAccount(string userNames[], string userPasswords[],int currentIndex, int &index, float userBalances[], float userInvestments[], string userIDs[])
{
    bool accountDeletion = false;
    userHeader();
    string currentPass;
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter you're Password: ";
    currentPass = getAnonymousPass();
    simulateProcessing();
    if(currentPass == userPasswords[currentIndex])
    {
        for (int i = currentIndex; i < index; i++)
        {
            userNames[i] = userNames[i+1];
            userPasswords[i] = userPasswords[i+1];
            userBalances[i] = userBalances[i+1];
            userInvestments[i] = userInvestments[i+1];
            userIDs[i] = userIDs[i+1];
        }
        index--;
        accountDeletion = true;
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYour account has been removed.";
    }
    else
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tInvalid Password.";
    
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
    return accountDeletion;
}
void transferNow(string userNames[], float userBalances[], int currentIndex, int transferIndex, float transfer)
{
    userBalances[currentIndex] -= transfer;               //  from user1
    userBalances[transferIndex] += transfer;              //   to user2
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully Transfered \"$" << transfer << "\" from you're account to the account of \"" << userNames[transferIndex] << "\"" << endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: $" << userBalances[currentIndex] << endl;
}
void invest(float userBalances[], float userInvestments[], int currentIndex, float investment, float goldinGrams)
{
    userBalances[currentIndex] -= investment;
    userInvestments[currentIndex] += goldinGrams;
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou have successfully invested \"$" << investment << "\" into " << goldinGrams << "-Gram of gold..";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tNew Balance: " << userBalances[currentIndex] << endl;
}
////////////////////////////////////////////////////////////////////////////////////////// user  functions  End  ////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////// input validation start //////////////////////////////////////////////////////////////////////////////////////////////////////////
void viewTransactionsHeader()
{
    cout << "\t\t\t\t\t\t\t\t       #################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t  Transaction Type\t     Amount($)" << endl;
    cout << "\t\t\t\t\t\t\t\t       #################################################" << endl << endl;                
}
void showBalance(float userBalances[], int currentIndex)
{
    cout << "\t\t\t\t\t\t\t\t\t\t\tYour Balance: $" << userBalances[currentIndex] << endl << endl;
}
void goldHeader(float goldRate)
{
    cout << "\t\t\t\t\t\t\t\t\t\t\t1-Gram of Gold = $" << goldRate << endl  << endl;
}
void transactionError()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tThe attempted transaction was not approved.\n";
}
void passNotCorrect()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tInvalid Password" << endl;
    setcolor(white);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
    getch();
}
void accountNotExists()
{
    setcolor(lightred);
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tAccount does'nt Exist" << endl;
    setcolor(white);
    cout << "\t\t\t\t\t\t\t\t\t\t\tPress any key to continue...";
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
bool nameCheck(string name)  ///username when signup
{
    bool found = true;
	for (int i = 0; i < name.length(); i++)
	{
		if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'))
            continue;
        else 
        {
            found = false;
            break;
        }
	}
	return found;
}
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
bool adminLoginCheck(string pass, string &adminPassword)
{
    bool login = false; 
    if (pass == adminPassword)
        login = true;
    return login;
}
void createUser(string userNames[], string userPasswords[], string userIDs[], int &index, string name, string pass)
{
    simulateProcessing();
    /// assigning values
    userNames[index] = name;
    userPasswords[index] = pass;
    userIDs[index] = "000"; 
    userIDs[index] += to_string(index+1);
    index++;  
    setcolor(lightgreen);
    cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t\tSuccessfully created new user" << endl;
    setcolor(white);
}
void invalidNameError()
{
    setcolor(lightred);
    cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid Name....";
    setcolor(white);
    simulateWithoutTellingLONG();                    
}
void simulateProcessing()
{
    setcolor(lightblue);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tProcessing please wait...";
    setcolor(white); 
    Sleep(800);
}
void simulateWithoutTellingLONG()
{
    Sleep(700);
}
void simulateWithoutTelling()
{
    Sleep(500);
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
void loader()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    int bar1=177,bar2=219;
    cout<< "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t\t\t\t   WAIT A MINUTE.....";
    cout<<"\n\n\n\t\t\t\t\t\t\t\t\t";
    for(int i=0;i<25;i++)
        cout<<(char)bar1;
    cout<<"\r";
    cout<<"\t\t\t\t\t\t\t\t\t";
    for(int i=0;i<25;i++)
    {
        cout<<(char)bar2;
        Sleep(50);
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// xtra functions
string getAdminPass()
{
    string userEnterAdminPass;
    setcolor(lightcyan);    
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter the Password: ";
    userEnterAdminPass = getAnonymousPass();       /// pass in  '***' format
    setcolor(white);
    return userEnterAdminPass;        
}
void accessDeniedError()
{
    setcolor(lightred);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tAccess Denied.............." << endl;
    setcolor(white);
}
string getUserEnteredName()
{
retakeNameInputSignIN:   // if invalid name then again
    signInHeader();
    string userEnteredName;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your User Name: ";
    cin >> userEnteredName;
    bool nameValidation = nameCheck(userEnteredName);
    if (!nameValidation)
    {
        invalidNameError();
        goto retakeNameInputSignIN;
    }
    setcolor(white);
    return userEnteredName;
}
string getNAME()
{
retakeNameInputSignUP:   // if invalid name then again
    signUpHeader();
    string name;
    setcolor(lightcyan);
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your name: ";
    cin >> name;
    bool nameValidation = nameCheck(name);
    if (!nameValidation)
    {
        invalidNameError();
        goto retakeNameInputSignUP;
    }
    return name;
}
void userAlreadyExists()
{
    setcolor(red);
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tUser Already Exists....";
}
void terminateProgram()
{
    setcolor(red);
    cout << "\t\t\t\t\t\t\t\t\t\t\tTerminating the program....";
    setcolor(white);
    simulateWithoutTelling();        
    system("cls");
}
void invalidChoiceError()
{
    setcolor(lightred); 
    cout << "\t\t\t\t\t\t\t\t\t\t\tInvalid choice....";
    setcolor(white);   
    simulateWithoutTelling(); 
}
//////////////////////////////////////////////////////////////////////////////////////   headers   end    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////// End of Program ////////////////////////////////////////////////////////////////////////////////////////////////////////////