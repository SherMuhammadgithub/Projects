#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
int BOARD_L = 7;
int BOARD_W = 8;
void displayBoard(char[][8]);
int getx();
int gety();
bool win(char [][8]);
bool horizontalWin(char [][8]);
bool verticalWin(char [][8]);
bool diagonalWin(char [][8]);
int main() 
{
    char board[7][8]=
   {
    "-------",
    "| | | |",
    "-------",
    "| | | |",
    "-------",
    "| | | |", 
    "-------"
    };
    system("cls");
    cout << "Welcome to Tic Tac Toe!" << endl;
    displayBoard(board);
    int x,y;
    int turn = 1; /// 1 = X's turn, 0 = O's turn
    /// getting the input
    while(true)
    {
        turn = 0;
        if (win(board))
            break;
        /// checking if the input is valid
        if (turn == 1)
        {
            cout << "Enter Your Move 'X' i.e(A0): ";
            x = getx();
            y = gety();
            if (board[x*2+1][y*2+1] == ' ')
            {
                board[x*2+1][y*2+1] = 'X';
                displayBoard(board);
            }
            else
            {
                cout << "Invalid Move!" << endl;
                continue;
            }
            turn = 0;
        }
        /// checking if the input is valid
        else if(turn == 0)
        {
            cout << "Enter Your Move 'O' i.e(A0): "; 
            x = getx();
            y = gety();
            if (board[x*2+1][y*2+1] == ' ')
            {
                board[x*2+1][y*2+1] = 'O';
                displayBoard(board);
            }
            else
            {
                cout << "Invalid Move!" << endl;
                continue;
            }
            turn = 1;
        }
    }
    /// END ///
    return 0;
}
bool win(char board[][8])
{
    /// checking for horizontal win
    bool horizontal = horizontalWin(board);
    bool vertical = false;//verticalWin(board);
    bool diagonal = diagonalWin(board);
    if (horizontal || vertical || diagonal)
        return true;
    return false;
}
bool diagonalWin(char board[][8])
{
    if (board[1][1] == board[3][3] && board[3][3] == board[5][5] && board[1][1] != ' ')
    {
        /// player symbol            
        cout << board[1][1] << " Wins!" << endl;
        return true;
    }
    else if (board[1][5] == board[3][3] && board[3][3] == board[5][1] && board[1][5] != ' ')
    {
        /// player symbol            
        cout << board[1][5] << " Wins!" << endl;
        return true;
    }
    return false;
}
bool verticalWin(char board[][8])
{
    for (int i = 1; i < BOARD_W; i+=2)
    {
        if (board[1][i] == board[3][i] && board[3][i] == board[5][i] && board[1][i] != ' ')
        {
                /// player symbol            
            cout << board[1][i] << " Wins!" << endl;
            return true;
        }
     }  
    return false;
}
bool horizontalWin(char board[][8])
{
    for (int i = 1; i < BOARD_L; i+=2)
    {
        if (board[i][1] == board[i][3] && board[i][3] == board[i][5] && board[i][1] != ' ')
        {
            /// player symbol            
            cout << board[i][1] << " Wins!" << endl;
            return true;
        }
    }
    return false;
}
int getx()
{
    char temp = 0;              /// temp because it'll be converted to int
    temp = getche();           /// getting char input
    int x = temp - 'A';       /// converting char to int
    return x;
}
int gety()
{
    int y = 0;
    cin >> y;                 /// single digit input
    return y;              /// returning the input
}
void displayBoard(char board[][8]) 
{
    int temp = 1;
    cout << " 0 1 2" << endl;  /// display's column letters
    for (int i = 0; i < BOARD_L; ++i) 
    {
        for (int j = 0; j < BOARD_W; ++j)
        {
            cout << board[i][j];
        }
        if (i%2 != 0)
        {
            if (temp == 1)
                cout << " " << 'A';  
            else if (temp == 2)
                cout << " " << 'B';    
            else if (temp == 3)
                cout << " " << 'C';    
            temp++;
        }
        cout << endl;
    }
}
