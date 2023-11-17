#include <iostream>
#include <windows.h>

using namespace std;

char getCharAtxy(short int x, short int y);
void gotoxy(int x, int y);

//
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


// enemy varaibles
int e1X = 2, e1Y = 1;
bool e1WallHit = false;

int e2X = 30, e2Y = 20;
bool e2WallHit = false;

int e3X = 69, e3Y = 1;
bool e3WallHit = false;

// player variables
int pX = 20, pY = 20;

// main
main(){
    system("cls");
    printMaze();

    gotoxy(0,23);
    header();
    
    score();

    printEnemy1();
    printEnemy2();
    printEnemy3();
    
    printPlayer();
    
    while(true){
        if (GetAsyncKeyState(VK_LEFT))
            movePlayerLeft();

        if (GetAsyncKeyState(VK_RIGHT))
            movePlayerRight();
        
        if (GetAsyncKeyState(VK_UP))
            movePlayerUp();
        
        if (GetAsyncKeyState(VK_DOWN))
            movePlayerDown();
      
        moveEnemy1();
        moveEnemy2();
        moveEnemy3();
    
        gotoxy(100,8);
        cout << bonus1;
        
        Sleep(100);


    }
}

// enemy one
void printEnemy1(){
    gotoxy(e1X,e1Y);
    cout << "@    @" << endl;
    gotoxy(e1X,e1Y+1);
    cout << "@_EE_@" << endl;
    gotoxy(e1X,e1Y+2);
    cout << "@ EE @" << endl;

}

void eraseEnemy1(){
    gotoxy(e1X,e1Y);
    cout << "      " << endl;
    gotoxy(e1X,e1Y+1);
    cout << "      " << endl;
    gotoxy(e1X,e1Y+2);
    cout << "      " << endl;
}

void moveEnemy1(){
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
void printEnemy2(){
    gotoxy(e2X,e2Y);
    cout << "@ EE @" << endl;
    gotoxy(e2X,e2Y+1);
    cout << "@_EE_@" << endl;
    gotoxy(e2X,e2Y+2);
    cout << "@    @" << endl;

}

void eraseEnemy2(){
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
void printEnemy3(){
    gotoxy(e3X,e3Y);
    cout << "@-@-@" << endl;
    gotoxy(e3X,e3Y+1);
    cout << "333| " << endl;
    gotoxy(e3X,e3Y+2);
    cout << "@-@-@" << endl;

}

void eraseEnemy3(){
    gotoxy(e3X,e3Y);
    cout << "     " << endl;
    gotoxy(e3X,e3Y+1);
    cout << "     " << endl;
    gotoxy(e3X,e3Y+2);
    cout << "     " << endl;

}

void moveEnemy3(){       
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
void printPlayer(){
    gotoxy(pX,pY);
    cout << "@ || @" << endl;
    gotoxy(pX,pY+1);
    cout << "@_||_@" << endl;
    gotoxy(pX,pY+2);
    cout << "@    @" << endl;
    
}

void erasePlayer(){
    gotoxy(pX,pY);
    cout << "      " << endl;
    gotoxy(pX,pY+1);
    cout << "      " << endl;
    gotoxy(pX,pY+2);
    cout << "      " << endl;
    
}

// player movements
void movePlayerLeft(){
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

    
void movePlayerRight(){
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

void movePlayerUp(){
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

void movePlayerDown(){
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

void printMaze(){

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



void header(){
    
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
char getCharAtxy(short int x, short int y){
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar: ' ';

}

void gotoxy(int x, int y){
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

}




////old headers

// void score(){
//     int x=80,y=1;

//     gotoxy(x,y);
//     cout << " #####     ####     ####     ######      #####"<< endl;
//     gotoxy(x,y+1);
//     cout << "#        ##       ##    ##   ##    ##   ##    "<< endl;
//     gotoxy(x,y+2);
//     cout << " ####    ##       ##    ##   ######     ####  "<< endl;
//     gotoxy(x,y+3);
//     cout << "     #   ##       ##    ##   ##   ##    ##    "<< endl;
//     gotoxy(x,y+4);
//     cout << "#####      ####     ####     ##    ##    #####"<< endl;

// }

// void header(){
//     cout << endl;
//     cout << "######     ###     ###   ##   ##   ##      ##      ##     ###     ######      #####  " << endl;
//     cout << "  ##     ##   ##   ## #  ##   ##  ##       ##      ##   ##   ##   ##    ##   ##      " << endl;
//     cout << "  ##     ### ###   ##  # ##   ####         ##  ##  ##   ### ###   ######      #####  " << endl;
//     cout << "  ##     ##   ##   ##   ###   ##  ##       ## #  # ##   ##   ##   ##   ##         ## " << endl;
//     cout << "  ##     ##   ##   ##    ##   ##   ##      ###    ###   ##   ##   ##    ##    #####  " << endl;

// }
