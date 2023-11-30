#include<iostream>
#include<conio.h>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y);
void printBoard(char[][21]);
void printBorder(char[][21]);
void fire(char[][21]);
void moveFire(char[][21], int step);
void removeFire(char[][21]);
void movePlayer(char[][21], char);
void moveEnemy(char [][21], char, char);
bool wallNotDetected(char[][21]);
void moveFire(char Board[][21]);
// void movePlayerLeft(char[][21]);
// void movePlayerRight(char[][21]);
int main()
{
    char Board[10][21] = {"####################",
                          "#                  #", 
                          "#        e         #", 
                          "#     x  e         #", 
                          "#                  #", 
                          "#                  #", 
                          "#        p         #", 
                          "#                  #",  
                          "####################"};
    printBoard(Board);
    while(true)
    {
        if(GetAsyncKeyState(VK_LEFT))
        {
            movePlayer(Board, 'l');
            printBoard(Board);
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer(Board, 'r');
            printBoard(Board);
        }
        // else if(GetAsyncKeyState(VK_SPACE))
        // {
        //     fire(Board);
        //     moveFire(Board, 1);
        //     printBoard(Board);
        //     removeFire(Board);
        //     printBoard(Board);
        // }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            fire(Board);    
            printBoard(Board);       
            bool flag = true;
            while (flag)
            {

                if (wallNotDetected(Board))
                {
                    moveFire(Board);
                    printBoard(Board);
                }
                else
                {
                    flag = false;
                    printBoard(Board);
                }
            }
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }
    return 0;
}
void removeFire(char Board[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == 'f')
            {
                Board[i][j] = ' ';
                break;
            }
        }
    }
}
void moveEnemy(char Board[][21], char enemyType, char move)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == enemyType)
            {
                Board[i][j] = ' ';
                if (move == 'r')     /// right
                {
                    if (j + 1 < 21 && Board[i][j + 1] == ' ')     /// wall collision
                    {
                        Board[i][j] = ' ';
                        Board[i][j + 1] = enemyType;
                        break;
                    }
                }
                else if (move == 'l')       /// left
                {
                    if (Board[i][j - 1] == ' ')
                    {
                        Board[i][j] = ' ';
                        Board[i][j-1] = enemyType;
                        break;
                    }  
                }
            }
        }
    }
}
void movePlayer(char Board[][21], char position)
{
   for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == 'p')
            {
                if (position == 'r')     /// right
                {
                    if (j + 1 < 21 && Board[i][j + 1] == ' ')     /// wall collision
                    {
                        Board[i][j] = ' ';
                        Board[i][j + 1] = 'p';
                        break;
                    }
                }
                else if (position == 'l')       /// left
                {
                    if (Board[i][j - 1] == ' ')
                    {
                        Board[i][j] = ' ';
                        Board[i][j-1] = 'p';
                        break;
                    }  
                }
            }

        }
    }
}

void moveFire(char Board[][21], int step)
{
    while(step != 0)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (Board[i][j] == 'f')
                {
                    Board[i][j] = ' ';
                    Board[i-1][j] = 'f';
                }
            }
        }
        step--;    
    }
}

void moveFire(char Board[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == 'f')
            {
                Board[i][j] = ' ';
                Board[i-1][j] = 'f';
            }
        }
    }
}


void fire(char Board[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == 'p')
            {
                Board[i-1][j] = 'f';
            }

        }
    }
}
// this functions will only print the border of the board
void printBorder(char Board[][21])
{
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            // apply if condition to print only the border
            // if the element is '#' or ' ' then print it
            if (Board[i][j] == '#' || Board[i][j] == ' ')
                cout << Board[i][j];
            else
                cout << ' ';
        }
        cout << endl;
    }   
}
void printBoard(char Board[][21])
{
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
                cout << Board[i][j];
        }
        cout << endl;
    }
}

// bool wallNotDetected(char arr[10][21])
// {
//     for (int i = 0; i < 10; i++)
//     {
//         for (int j = 0; j < 21; j++)
//         {
//             if (j==20)
//             {
//                 arr[i][j] = ' ';  // remove fire
//                 return false; // Collision detected, stop moving
//             }
//         }
//     }
//     return true; // No collision detected, continue moving
// }
bool wallNotDetected(char arr[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (arr[i][j] == 'f' && arr[i - 1][j] == '#')
            {
                arr[i][j] = ' ';  // remove fire
                return false; // Collision detected, stop moving
            }
        }
    }
    return true; // No collision detected, continue moving
}
///// old separte functions     ;}
// void movePlayerLeft(char Board[][21])
// {
//     for (int i = 0; i < 10; i++)
//     {
//         for (int j = 0; j < 21; j++)
//         {
//             if (Board[i][j] == 'p')
//             {
//                 if (Board[i][j + 1] == ' ')
//                 {
//                     Board[i][j] = ' ';
//                     Board[i][j-1] = 'p';
//                 }
//             }
//         }
//     }
// }
// void movePlayerRight(char Board[][21])
// {
//     for (int i = 0; i < 10; i++)
//     {
//         for (int j = 0; j < 21; j++)
//         {
//             if (Board[i][j] == 'p')
//             {
//                 if (j + 1 < 21 && Board[i][j + 1] == ' ')
//                 {
//                     // Move player to the right if the next position is empty
//                     Board[i][j] = ' ';
//                     Board[i][j + 1] = 'p';
//                     break;
//                 }
//             }
//         }
//     }
// }
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

}