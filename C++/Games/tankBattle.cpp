#include <iostream>
#include <windows.h>
using namespace std;
//////////////////////////
char getCharAtxy(short int x, short int y);
void gotoxy(int x, int y);//
int bonus1 = 0; 
// enemy one
void printEnemy1();
void eraseEnemy1();
void moveEnemy1();
// enemy two
void printEnemy2();
void eraseEnemy2();
void moveEnemy2();
// enemy three
void printEnemy3();
void eraseEnemy3();
void moveEnemy3();
// player
void erasePlayer();
void printPlayer();
// maze
void printMaze();
// header
void header();
//
void score();
// player movement
void movePlayerLeft();
void movePlayerRight();
void movePlayerUp();
void movePlayerDown();
/////////////////////// enemy varaibles
int e1X = 2, e1Y = 1;
bool e1WallHit = false;
///
int e2X = 30, e2Y = 20;
bool e2WallHit = false;
///
int e3X = 69, e3Y = 1;
bool e3WallHit = false;
// player variables
int pX = 20, pY = 20;
/////////////////////////////////////
void changeFirePosition();
void playerFire();
void moveFire();
void printScores();
///////////////
bool fired = false;
int bulletX = 0;
int bulletY = 0;
int playerHealth = 3;
int enemy1Health = 3;
int enemy2Health = 3;
int enemy3Health = 3;
/////
bool horizontal = true;
bool vertical = false;
bool dead1 = false;
bool dead2 = false;
bool dead3 = false;
// main
int main()
{
    system("cls");
    printMaze();

    gotoxy(0,23);
    header();
    
    score();

    printEnemy1();
    printEnemy2();
    printEnemy3();
    
    printPlayer();
    
    while(true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
        }
        if (GetAsyncKeyState('F'))
        {
            if (!fired)
            {
                changeFirePosition();
                printPlayer();
            } 
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            if (!fired)
            {
                playerFire();
                fired = true;
            }
        }
        if (fired)
        {
            moveFire();
        }
        if (enemy1Health != 0)
        {
            moveEnemy1();
        }
        if (dead1)
        {
            eraseEnemy1();
            dead1 = false;
        }
        if (enemy2Health != 0)
        {
            moveEnemy2();
        }
        if (dead2)
        {
            eraseEnemy2();
            dead2 = false;
        }
        if (enemy3Health != 0)
        {
            moveEnemy3();
        }
        if (dead3)
        {
            eraseEnemy3();
            dead3 = false;
        }
        if (enemy1Health == 0 && enemy2Health == 0 && enemy3Health == 0)
        {
            gotoxy(80,15);
            cout << "You Win";
            gotoxy(80,16);
            cout << "Your Score: " << bonus1;
            gotoxy(80,17);
            cout << "Press any key to exit";
            system("cls");
            break;
        }
        printScores();
        Sleep(100);
    }
}
void printScores()
{
    gotoxy(85,9);
    cout << "Points";
    gotoxy(100,9);
    cout << bonus1;
    gotoxy(80,10);
    cout << "Player Health";
    gotoxy(100,10);
    cout << playerHealth;
    
    gotoxy(80,11);
    cout << "Enemy One Health";
    gotoxy(100,11);
    cout << enemy1Health;
    gotoxy(80,12);
    cout << "Enemy Two Health";
    gotoxy(100,12);
    cout << enemy2Health;
    gotoxy(80,13);
    cout << "Enemy Three Health";
    gotoxy(100,13);
    cout << enemy3Health;
}
void moveFire()
{
    if (horizontal)
    {

        gotoxy(bulletX,bulletY);
        cout << " ";
        gotoxy(bulletX,bulletY-1);
        cout << "^";
        if (getCharAtxy(bulletX, bulletY - 2) == ' ')
        {
            bulletY = bulletY - 1;
        }
        else if (getCharAtxy(bulletX, bulletY - 2) == '@' || getCharAtxy(bulletX, bulletY - 2) == 'E')
        {
            bonus1 += 5;
            gotoxy(bulletX,bulletY-1);
            cout << " ";
            fired = false;
            enemy1Health--;
            if (enemy1Health == 0)
            {
                dead1 = true;
            }
        }
        else if (getCharAtxy(bulletX, bulletY - 2) == '|' || getCharAtxy(bulletX, bulletY - 2) == 'e')
        {
            bonus1 += 5;
            gotoxy(bulletX,bulletY-1);
            cout << " ";
            fired = false;
            enemy2Health--;
            if (enemy2Health == 0)
            {
                dead2 = true;
            }
        }
        else if (getCharAtxy(bulletX, bulletY - 2) == '-' || getCharAtxy(bulletX, bulletY - 2) == 'j'|| getCharAtxy(bulletX, bulletY - 2) == '0')
        {
            bonus1 += 5;
            gotoxy(bulletX,bulletY-1);
            cout << " ";
            fired = false;
            enemy3Health--;
            if (enemy3Health == 0)
            {
                dead3 = true;
            }
        }
        else
        {
            gotoxy(bulletX,bulletY-1);
            cout << " ";
            fired = false;
        }
    }
    else if (vertical)
    {
        gotoxy(bulletX,bulletY);
        cout << " ";
        gotoxy(bulletX+1,bulletY);
        cout << ">";
        if (getCharAtxy(bulletX + 3, bulletY) == ' ')
        {
            bulletX = bulletX + 1;
        }
        else if (getCharAtxy(bulletX + 3, bulletY) == '@' || getCharAtxy(bulletX + 3, bulletY) == 'E')
        {
            bonus1 += 5;
            gotoxy(bulletX, bulletY-1);
            cout << " ";
            fired = false;
            enemy1Health--;
            if (enemy1Health == 0)
            {
                dead1 = true;
            }
        }
        else if (getCharAtxy(bulletX + 3, bulletY) == '|' || getCharAtxy(bulletX + 3, bulletY) == 'e')
        {
            bonus1 += 5;
            gotoxy(bulletX,bulletY-1);
            cout << " ";
            fired = false;
            enemy2Health--;
            if (enemy2Health == 0)
            {
                dead2 = true;
            }
        }
        else if (getCharAtxy(bulletX + 3, bulletY) == '-' || getCharAtxy(bulletX + 3, bulletY) == 'j'|| getCharAtxy(bulletX, bulletY) == '0')
        {
            bonus1 += 5;
            gotoxy(bulletX,bulletY-1);
            cout << " ";
            fired = false;
            enemy3Health--;
            if (enemy3Health == 0)
            {
                dead3 = true;
            }
        }
        else
        {
            gotoxy(bulletX+1,bulletY);
            cout << " ";
            fired = false;
        }
    }
}

void playerFire()
{
    if (horizontal)
    {
        bulletX = pX + 2;
        bulletY = pY - 1;
        gotoxy(bulletX, bulletY);
        cout << "^";
    }
    else if (vertical)
    {
        bulletX = pX + 2;
        bulletY = pY - 1;
        gotoxy(bulletX, bulletY);
        cout << ">";
    }
}
void changeFirePosition()
{
    if (horizontal)
    {
        vertical = true;
        horizontal = false;
    }
    else if (vertical)
    {
        vertical = false;
        horizontal = true;
    }
}
// enemy one
void printEnemy1()
{
    gotoxy(e1X,e1Y);
    cout << "@    @" << endl;
    gotoxy(e1X,e1Y+1);
    cout << "@_EE_@" << endl;
    gotoxy(e1X,e1Y+2);
    cout << "@ EE @" << endl;

}
void eraseEnemy1()
{
    gotoxy(e1X,e1Y);
    cout << "      " << endl;
    gotoxy(e1X,e1Y+1);
    cout << "      " << endl;
    gotoxy(e1X,e1Y+2);
    cout << "      " << endl;
}
void moveEnemy1()
{
    eraseEnemy1();    
    if (!e1WallHit){     
        e1X = e1X + 1;
        if(e1X == 42)
            e1WallHit = true;
    }
    else if(e1WallHit){ 
        e1X = e1X - 1;
        if(e1X < 3)
            e1WallHit = false;
    }
    printEnemy1();
}
// enemy two 
void printEnemy2()
{
    gotoxy(e2X,e2Y);
    cout << "| ee |" << endl;
    gotoxy(e2X,e2Y+1);
    cout << "|_ee_|" << endl;
    gotoxy(e2X,e2Y+2);
    cout << "|    |" << endl;
}
void eraseEnemy2()
{
    gotoxy(e2X,e2Y);
    cout << "      " << endl;
    gotoxy(e2X,e2Y+1);
    cout << "      " << endl;
    gotoxy(e2X,e2Y+2);
    cout << "      " << endl;
}
void moveEnemy2()
{
    eraseEnemy2();
    if (!e2WallHit){        
        e2X = e2X + 1;
        e2Y = e2Y - 1;
        if(e2X == 43)
            e2WallHit = true;
    }    
    else if(e2WallHit){ 
        e2X = e2X - 1;
        e2Y = e2Y + 1;
        if(e2X == 30)
            e2WallHit = false;
    }
    printEnemy2();
}
// enemy three
void printEnemy3()
{
    gotoxy(e3X,e3Y);
    cout << "0-0-0" << endl;
    gotoxy(e3X,e3Y+1);
    cout << "jjj| " << endl;
    gotoxy(e3X,e3Y+2);
    cout << "0-0-0" << endl;
}
void eraseEnemy3()
{
    gotoxy(e3X,e3Y);
    cout << "     " << endl;
    gotoxy(e3X,e3Y+1);
    cout << "     " << endl;
    gotoxy(e3X,e3Y+2);
    cout << "     " << endl;
}
void moveEnemy3()
{       
    eraseEnemy3();
    if (!e3WallHit){        
        e3Y = e3Y + 1;
        if(e3Y == 20)
            e3WallHit = true;
    }
    else if(e3WallHit){
        e3Y = e3Y - 1;
        if(e3Y < 2)
            e3WallHit = false;
    }
    printEnemy3();
}
// player  
void printPlayer()
{
    if (horizontal)
    {
        gotoxy(pX,pY);
        cout << "@ || @" << endl;
        gotoxy(pX,pY+1);
        cout << "@_||_@" << endl;
        gotoxy(pX,pY+2);
        cout << "@    @" << endl;    
    }
    else if (vertical)
    {
        gotoxy(pX,pY);
        cout << "@ //  " << endl;
        gotoxy(pX,pY+1);
        cout << "@_||_@" << endl;
        gotoxy(pX,pY+2);
        cout << "@    @" << endl;    
    }
}
void erasePlayer()
{
    gotoxy(pX,pY);
    cout << "      " << endl;
    gotoxy(pX,pY+1);
    cout << "      " << endl;
    gotoxy(pX,pY+2);
    cout << "      " << endl;    
}
// player movements
void movePlayerLeft()
{
    if (getCharAtxy(pX - 1, pY)== '*' || getCharAtxy(pX - 1, pY + 1) == '*' || getCharAtxy(pX - 1, pY + 2) == '*'){
        bonus1 += 1;
        erasePlayer();
        pX = pX - 1;
        printPlayer();
    }        
    else if (getCharAtxy(pX - 1, pY) == ' ' && getCharAtxy(pX - 1, pY + 1) == ' ' && getCharAtxy(pX - 1, pY + 2) == ' '){
        erasePlayer();
        pX = pX - 1;
        printPlayer();
    }    
}
void movePlayerRight()
{
    if (getCharAtxy(pX + 6, pY)== '*' || getCharAtxy(pX + 6, pY + 1) == '*' || getCharAtxy(pX + 6, pY + 2) == '*'){
        bonus1 += 1;
        erasePlayer();
        pX = pX + 1;
        printPlayer();
    }    
    else if (getCharAtxy(pX + 6, pY) == ' ' && getCharAtxy(pX + 6, pY + 1) == ' ' && getCharAtxy(pX + 6, pY + 2) == ' '){       
        erasePlayer();
        pX = pX + 1;
        printPlayer();
    }
}
void movePlayerUp()
{
    if (getCharAtxy(pX , pY - 1) == '*' || getCharAtxy(pX + 1 , pY - 1) == '*' || getCharAtxy(pX + 2, pY - 1) == '*' || getCharAtxy(pX + 3, pY - 1) == '*'|| getCharAtxy(pX + 4, pY - 1) == '*'|| getCharAtxy(pX + 5, pY - 1) == '*'){
        bonus1 +=1;
        erasePlayer();
        pY = pY - 1;
        printPlayer();
    } 
    else if(getCharAtxy(pX , pY - 1) == ' ' && getCharAtxy(pX + 1 , pY - 1) == ' ' && getCharAtxy(pX + 2, pY - 1) == ' '&& getCharAtxy(pX + 3, pY - 1) == ' '&& getCharAtxy(pX + 4, pY - 1) == ' '&& getCharAtxy(pX + 5, pY - 1) == ' '){
        erasePlayer();
        pY = pY - 1;
        printPlayer();
    }    
}
void movePlayerDown()
{
   if (getCharAtxy(pX , pY + 3) == '*' || getCharAtxy(pX + 1 , pY + 3) == '*' || getCharAtxy(pX + 2, pY + 3) == '*' || getCharAtxy(pX + 3, pY + 3) == '*'|| getCharAtxy(pX + 4, pY + 3) == '*'|| getCharAtxy(pX + 5, pY + 3) == '*'){
        bonus1 +=1;
        erasePlayer();
        pY = pY + 1;
        printPlayer();
    }
    else if(getCharAtxy(pX , pY + 3) == ' ' && getCharAtxy(pX + 1, pY + 3) == ' ' && getCharAtxy(pX + 2, pY + 3) == ' ' && getCharAtxy(pX + 3, pY + 3) == ' ' && getCharAtxy(pX + 4, pY + 3) == ' ' && getCharAtxy(pX + 5, pY + 3) == ' '){    
        erasePlayer();
        pY = pY + 1;
        printPlayer();
    }
}
void printMaze()
{

    cout << "#############################################################################" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                                              ##                         ##" << endl;
    cout << "##                                              ##                         ##" << endl;
    cout << "##             ##                                           ##             ##" << endl;
    cout << "##          *  ##                                *          ##    *        ##" << endl;
    cout << "##             ##           ###                             ##             ##" << endl;
    cout << "##       #######            ###                              ######        ##" << endl;
    cout << "##                                              ##                         ##" << endl;
    cout << "##                                              ##                         ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                           *                                             ##" << endl;
    cout << "##                                                *              *         ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                         ##                                              ##" << endl;
    cout << "##                         ##                  ##                          ##" << endl;
    cout << "##                                             ##                          ##" << endl;
    cout << "##        ######                                             ######        ##" << endl;
    cout << "##             ##                                           ##             ##" << endl;
    cout << "##             ##                                           ##    *        ##" << endl;
    cout << "##             ##          ##                               ##             ##" << endl;
    cout << "##                         ##                                              ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "#############################################################################" << endl;
}
void header()
{    
    cout << endl;
    cout << endl;
    cout << endl;

    cout<<R"(     _________  ________  ________   ___  __                                  )"<<endl;    
    cout<<R"(    |\___   ___\\   __  \|\   ___  \|\  \|\  \                                )"<<endl;    
    cout<<R"(    \|___ \  \_\ \  \|\  \ \  \\ \  \ \  \/  /|_                              )"<<endl;    
    cout<<R"(         \ \  \ \ \   __  \ \  \\ \  \ \   ___  \                             )"<<endl;    
    cout<<R"(          \ \  \ \ \  \ \  \ \  \\ \  \ \  \\ \  \                            )"<<endl;    
    cout<<R"(           \ \__\ \ \__\ \__\ \__\\ \__\ \__\\ \__\                           )"<<endl;    
    cout<<R"(            \|__|  \|__|\|__|\|__|_\|__|\|__| \|__|                           )"<<endl;
    cout<<R"(                             ___       ___  _________ ________  ________      )"<<endl;
    cout<<R"(                            |\  \     |\  \|\   __  \|\   __  \|\   ____\     )"<<endl;
    cout<<R"(                            \ \  \    \ \  \ \  \|\  \ \  \|\  \ \  \___|_    )"<<endl;
    cout<<R"(                             \ \  \  __\ \  \ \   __  \ \   _  _\ \_____  \   )"<<endl;
    cout<<R"(                              \ \  \|\__\_\  \ \  \ \  \ \  \\  \\|____|\  \  )"<<endl;
    cout<<R"(                               \ \____________\ \__\ \__\ \__\\ _\ ____\_\  \ )"<<endl;
    cout<<R"(                                \|____________|\|__|\|__|\|__|\|__|\_________\)"<<endl;
    cout<<R"(                                                                  \|_________|)"<<endl;                                                                     
}
void score() 
{
    int x = 80, y = 1; 

    gotoxy(x,y);
    cout << R"(  ________  ________  ________  ________  _______      )" << endl;
    
    gotoxy(x,y+1);
    cout << R"( |\   ____\|\   ____\|\   __  \|\   __  \|\  ___ \     )" << endl;
    
    gotoxy(x,y+2);
    cout << R"( \ \  \___|\ \  \___|\ \  \|\  \ \  \|\  \ \   __/|    )" << endl;
    
    gotoxy(x,y+3);
    cout << R"(  \ \_____  \ \  \    \ \  \\\  \ \   _  _\ \  \_|/__  )" << endl;
    
    gotoxy(x,y+4);
    cout << R"(   \|____|\  \ \  \____\ \  \\\  \ \  \\  \\ \  \_|\ \ )" << endl;
    
    gotoxy(x,y+5);
    cout << R"(     ____\_\  \ \_______\ \_______\ \__\\ _\\ \_______\)" << endl;
    
    gotoxy(x,y+6);
    cout << R"(    |\_________\|_______|\|_______|\|__|\|__|\|_______|)" << endl;
    
    gotoxy(x,y+7);
    cout << R"(    \|_________|                                       )" << endl;
}
// functions for game
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar: ' ';
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}