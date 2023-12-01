#include <iostream>
using namespace std;
int BOARD_L = 7;
int BOARD_W = 8;
void displayBoard(char[][8]);
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
    // cout << "Welcome to Tic Tac Toe!" << endl;
    // int move;
    // cout << "Enter Your Move: ";
    // cin >> move;


    displayBoard(board);
    return 0;
}
void displayBoard(char board[][8]) 
{
    cout << " A B C" << endl;  /// display's column letters
    for (int i = 0; i < BOARD_L; ++i) {
        for (int j = 0; j < BOARD_W; ++j) {
            cout << board[i][j];
        }
        if (i%2 != 0)
            cout << i/2 + 1;    /// display's row numbers
        cout << endl;
    }
}