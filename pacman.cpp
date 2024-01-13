#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <math.h>
using namespace std;

//______Prototypes______
void load();
void display();
void gotoxy(int x, int y);
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void calculateScore();
void printScore();
bool allGhosts();
int ghostDirection1();
bool ghostMovement1();
int ghostDirection2();
bool ghostMovement2();
int ghostDirection3();
bool ghostMovement3();
int ghostDirection4();
bool ghostMovement4();
void energy();

//_______Maze_______
char maze[24][71];

//_______Pacman______
int pacX = 9;
int pacY = 31;

//______Ghosts_____
int ghostX1 = 19;
int ghostY1 = 25;
int ghostX2 = 22;
int ghostY2 = 37;
int ghostX3 = 8;
int ghostY3 = 66;
int ghostX4 = 6;
int ghostY4 = 8;

//______Energizer_____
int energizerX1 = 12;
int energizerY1 = 14;
int energizerX2 = 6;
int energizerY2 = 63;

//______Others______
int score = 0;
char previousItem;
int countG2 = 37;
int countG3 = 8;

main()
{
    bool gamerunning = true;

    load();
    system("cls");
    display();

    maze[energizerX1][energizerY1] = 'O';
    gotoxy( energizerX1, energizerY1);
    cout <<maze[energizerX1][energizerY1];

    maze[energizerX2][energizerY2] = 'O';
    gotoxy( energizerX2, energizerY2);
    cout <<maze[energizerX2][energizerY2];

    maze[pacX][pacY] = 'P';
    gotoxy( pacX, pacY);
    cout << maze[pacX][pacY];

    maze[ghostX1][ghostY1] = 'G';
    gotoxy( ghostX1, ghostY1);
    cout <<maze[ghostX1][ghostY1];

    maze[ghostX2][ghostY2] = 'G';
    gotoxy( ghostX2, ghostY2);
    cout <<maze[ghostX2][ghostY2];

    maze[ghostX3][ghostY3] = 'G';
    gotoxy( ghostX3, ghostY3);
    cout <<maze[ghostX3][ghostY3];

    maze[ghostX4][ghostY4] = 'G';
    gotoxy( ghostX4, ghostY4);
    cout <<maze[ghostX4][ghostY4];

    for( int i = 0; i < 3; i++)
    {
        gamerunning = true;

    while ( gamerunning )
    {
        Sleep(50);   
        gamerunning = allGhosts();

        if ( GetAsyncKeyState(VK_LEFT) )
        {
            movePacmanLeft();
        }

        if ( GetAsyncKeyState(VK_RIGHT) )
        {
            movePacmanRight();
        }

        if ( GetAsyncKeyState(VK_UP) )
        {
            movePacmanUp();
        }

        if ( GetAsyncKeyState(VK_DOWN) )
        {
            movePacmanDown();
        }
        
        if ( GetAsyncKeyState(VK_ESCAPE) )
        {
            gamerunning = false;
        }
    }

    maze[pacX][pacY] = ' ';
    gotoxy(pacX, pacY);
    cout <<maze[pacX][pacY];

    maze[ghostX1][ghostY1] = ' ';
    gotoxy(ghostX1, ghostY1);
    cout <<maze[ghostX1][ghostY1];

    maze[ghostX2][ghostY2] = ' ';
    gotoxy(ghostX2, ghostY2);
    cout <<maze[ghostX2][ghostY2];

    maze[ghostX3][ghostY3] = ' ';
    gotoxy(ghostX3, ghostY3);
    cout <<maze[ghostX3][ghostY3];
    
    pacX = 9;
    pacY = 31;
    maze[pacX][pacY] = 'P';
    gotoxy(pacX, pacY);
    cout <<maze[pacX][pacY];

    ghostX1 = 19;
    ghostY1 = 25;
    maze[ghostX1][ghostY1] = 'G';
    gotoxy(ghostX1, ghostY1);
    cout <<maze[ghostX1][ghostY1];

    ghostX2 = 22;
    ghostY2 = 37;
    maze[ghostX2][ghostY2] = 'G';
    gotoxy(ghostX2, ghostY2);
    cout <<maze[ghostX2][ghostY2];

    ghostX3 = 8;
    ghostY3 = 66;
    maze[ghostX3][ghostY3] = 'G';
    gotoxy(ghostX3, ghostY3);
    cout <<maze[ghostX3][ghostY3];

    ghostX4 = 6;
    ghostY4 = 8;
    maze[ghostX4][ghostY4] = 'G';
    gotoxy(ghostX4, ghostY4);
    cout <<maze[ghostX4][ghostY4];

    }
}
//__________________________file load
void load()
{
    fstream file;
    string line;
    int r = 0;

    file.open( "grid.txt", ios :: in);
    while( getline( file, line ) )
    {
        for (int c = 0; c < 71; c++)
        {
            maze[r][c] = line[c];
        }
        r ++;
    }
    file.close();
}

//____________________________display maze
void display()
{
    for (int r = 0; r < 24; r++)
    {
        for (int c = 0; c < 71; c++)
        {
            cout <<maze[r][c];
        }
        cout <<endl;
    }
}

//___________________________score
void calculateScore()
{
    score = score + 1;
    printScore();
}
void printScore()
{
    gotoxy(4,75);
    cout <<"Score: " <<score;
}

//_________________________gotoxy
void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = y;
    coordinate.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

//________________________pacman movement
void movePacmanLeft()
{
    if ( maze[pacX][pacY - 1] == ' ' || maze[pacX][pacY - 1] == '.' || maze[pacX][pacY - 1] == 'O')
    {
        maze[pacX][pacY] = ' ';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
        pacY = pacY - 1;

        if ( maze[pacX][pacY] == '.' )
        {
          calculateScore();
        }
        if ( maze[pacX][pacY] == 'O')
        {
            energy();
        }
        
        maze[pacX][pacY] = 'P';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
    }
}

void movePacmanRight()
{
    if ( maze[pacX][pacY + 1] == ' ' || maze[pacX][pacY + 1] == '.' || maze[pacX][pacY + 1] == 'O')
    {
        maze[pacX][pacY] = ' ';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
        pacY = pacY + 1;

        if ( maze[pacX][pacY] == '.' )
        {
           calculateScore();
        }

        if ( maze[pacX][pacY] == 'O')
        {
            energy();
        }
        maze[pacX][pacY] = 'P';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
    }
}

void movePacmanUp()
{
    if ( maze[pacX - 1][pacY] == ' ' || maze[pacX - 1][pacY] == '.' || maze[pacX - 1][pacY] == 'O')
    {
        maze[pacX][pacY] = ' ';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
        pacX = pacX - 1;

        if ( maze[pacX][pacY] == '.' )
        {
            calculateScore();
        }

        if ( maze[pacX][pacY] == 'O')
        {
            energy();
        }

        maze[pacX][pacY] = 'P';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
    }
}

void movePacmanDown()
{
    if ( maze[pacX + 1][pacY] == ' ' || maze[pacX + 1][pacY] == '.' || maze[pacX + 1][pacY] == 'O')
    {
        maze[pacX][pacY] = ' ';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
        pacX = pacX + 1;

        if ( maze[pacX][pacY] == '.' )
        {
            calculateScore();
        }

        if ( maze[pacX][pacY] == 'O')
        {
            energy();
        }

        maze[pacX][pacY] = 'P';
        gotoxy(pacX, pacY);
        cout <<maze[pacX][pacY];
    }
}

//________________________Ghosts directions
int ghostDirection1()
{
    if(ghostX1 > pacX)
    {
        if ( maze[ghostX1 - 1][ghostY1] != '|' && maze[ghostX1 - 1][ghostY1] != '#' && maze[ghostX1 - 1][ghostY1] != '%' )
        {
            return 3;
        }
    }
    if(ghostY1 > pacY)
    {
        if ( maze[ghostX1][ghostY1 - 1] != '|' && maze[ghostX1][ghostY1 - 1] != '#' && maze[ghostX1][ghostY1 - 1] != '%' )
        {
            return 1;
        }
    }
    if(ghostX1 < pacX)
    {
        if ( maze[ghostX1 + 1][ghostY1] != '|' && maze[ghostX1 + 1][ghostY1] != '#' && maze[ghostX1 + 1][ghostY1] != '%' )
        {
            return 4;
        }
    }
    if(ghostY1 < pacY)
    {
        if ( maze[ghostX1][ghostY1 + 1] != '|' && maze[ghostX1][ghostY1 + 1] != '#' && maze[ghostX1][ghostY1 + 1] != '%' )
        {
            return 2;
        }
    }
}

int ghostDirection2()
{
    if ( countG2 < 65 && countG2 > 0 )
    {
        countG2 ++;
        if (countG2 == 64)
        {
            countG2 = -1;
        }
        return 1;
    }

    if ( countG2 > -65 && countG2 < 0 )
    {
        countG2 --;
        if (countG2 == -64)
        {
            countG2 = 1;
        }
        return 2;
    }
}

int ghostDirection3()
{
    if ( countG3 < 22 && countG3 > 0 )
    {
        countG3 ++;
        if (countG3 == 21)
        {
            countG3 = -1;
        }
        return 3;
    }

    if ( countG3 > -22 && countG3 < 0 )
    {
        countG3 --;
        if (countG3 == -21)
        {
            countG3 = 1;
        }
        return 4;
    }
}

int ghostDirection4()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

//__________________________Ghosts movements
bool allGhosts()
{
    if  (ghostMovement1() && ghostMovement2() && ghostMovement3() && ghostMovement4() )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool ghostMovement1()
{
    int value = ghostDirection1();

    if ( value == 1 ) //move left
    {
        if ( maze[ghostX1][ghostY1 - 1] == ' ' || maze[ghostX1][ghostY1 - 1] == '.' || maze[ghostX1][ghostY1 - 1] == 'P' || maze[ghostX1][ghostY1 - 1] == 'O')
        {
            maze[ghostX1][ghostY1] = previousItem;
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
            ghostY1 = ghostY1 - 1;
            previousItem = maze[ghostX1][ghostY1];
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];

            if (previousItem == 'P')
            {
                maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
        }
    }

    if ( value == 2) //move right
    {
        if ( maze[ghostX1][ghostY1 + 1] ==' ' || maze[ghostX1][ghostY1 + 1] == '.' || maze[ghostX1][ghostY1 + 1] == 'P' || maze[ghostX1][ghostY1 + 1] == 'O')
        {
            maze[ghostX1][ghostY1] = previousItem;
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
            ghostY1 = ghostY1 + 1;
            previousItem = maze[ghostX1][ghostY1];
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];

            if (previousItem == 'P')
            {
                maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
        }
    }
    
    if ( value == 3) //move up
    {
        if ( maze[ghostX1 - 1][ghostY1] ==' ' || maze[ghostX1 - 1][ghostY1] == '.' || maze[ghostX1 - 1][ghostY1] == 'P' || maze[ghostX1 - 1][ghostY1] == 'O')
        {
            maze[ghostX1][ghostY1] = previousItem;
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
            ghostX1 = ghostX1 - 1;
            previousItem = maze[ghostX1][ghostY1];
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];

            if (previousItem == 'P')
            {
                maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
        }
    }
    
    if ( value == 4) //move down
    {
        if ( maze[ghostX1 + 1][ghostY1] ==' ' || maze[ghostX1 + 1][ghostY1] == '.' || maze[ghostX1 + 1][ghostY1] == 'P' || maze[ghostX1 + 1][ghostY1] == 'O')
        {
            maze[ghostX1][ghostY1] = previousItem;
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
            ghostX1 = ghostX1 + 1;
            previousItem = maze[ghostX1][ghostY1];
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];

            if (previousItem == 'P')
            {
                maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
            gotoxy( ghostX1, ghostY1);
            cout <<maze[ghostX1][ghostY1];
        }
    }
    return 1;
}

bool ghostMovement2()
{
    int value = ghostDirection2();

    if ( value == 1 ) //move left
    {
        if ( maze[ghostX2][ghostY2 - 1] == ' ' || maze[ghostX2][ghostY2 - 1] == '.' || maze[ghostX2][ghostY2 - 1] == 'P')
        {
            maze[ghostX2][ghostY2] = previousItem;
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];
            ghostY2 = ghostY2 - 1;
            previousItem = maze[ghostX2][ghostY2];
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];

            if (previousItem == 'P')
            {
                maze[ghostX2][ghostY2] = 'G';
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];
                return 0;
            }
            maze[ghostX2][ghostY2] = 'G';
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];
        }
    }

    if ( value == 2) //move right
    {
        if ( maze[ghostX2][ghostY2 + 1] ==' ' || maze[ghostX2][ghostY2 + 1] == '.' || maze[ghostX2][ghostY2 + 1] == 'P')
        {
            maze[ghostX2][ghostY2] = previousItem;
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];
            ghostY2 = ghostY2 + 1;
            previousItem = maze[ghostX2][ghostY2];
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];

            if (previousItem == 'P')
            {
                maze[ghostX2][ghostY2] = 'G';
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];
                return 0;
            }
            maze[ghostX2][ghostY2] = 'G';
            gotoxy( ghostX2, ghostY2);
            cout <<maze[ghostX2][ghostY2];
        }
    }
    return 1;
}

bool ghostMovement3()
{
    int value = ghostDirection3();

    if ( value == 3) //move up
    {
        if ( maze[ghostX3 - 1][ghostY3] ==' ' || maze[ghostX3 - 1][ghostY3] == '.' || maze[ghostX3 - 1][ghostY3] == 'P')
        {
            maze[ghostX3][ghostY3] = previousItem;
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];
            ghostX3 = ghostX3 - 1;
            previousItem = maze[ghostX3][ghostY3];
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];

            if (previousItem == 'P')
            {
                maze[ghostX3][ghostY3] = 'G';
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];
                return 0;
            }
            maze[ghostX3][ghostY3] = 'G';
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];
        }
    }
    
    if ( value == 4) //move down
    {
        if ( maze[ghostX3 + 1][ghostY3] ==' ' || maze[ghostX3 + 1][ghostY3] == '.' || maze[ghostX3 + 1][ghostY3] == 'P')
        {
            maze[ghostX3][ghostY3] = previousItem;
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];
            ghostX3 = ghostX3 + 1;
            previousItem = maze[ghostX3][ghostY3];
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];

            if (previousItem == 'P')
            {
                maze[ghostX3][ghostY3] = 'G';
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];
                return 0;
            }
            maze[ghostX3][ghostY3] = 'G';
            gotoxy( ghostX3, ghostY3);
            cout <<maze[ghostX3][ghostY3];
        }
    }
    return 1;
}

bool ghostMovement4()
{
    int value = ghostDirection4();

    if ( value == 1 ) //move left
    {
        if ( maze[ghostX4][ghostY4 - 1] == ' ' || maze[ghostX4][ghostY4 - 1] == '.' || maze[ghostX4][ghostY4 - 1] == 'P' || maze[ghostX4][ghostY4 - 1] == 'O')
        {
            maze[ghostX4][ghostY4] = previousItem;
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
            ghostY4 = ghostY4 - 1;
            previousItem = maze[ghostX4][ghostY4];
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];

            if (previousItem == 'P')
            {
                maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
        }
    }

    if ( value == 2) //move right
    {
        if ( maze[ghostX4][ghostY4 + 1] ==' ' || maze[ghostX4][ghostY4 + 1] == '.' || maze[ghostX4][ghostY4 + 1] == 'P' || maze[ghostX4][ghostY4 + 1] == 'O')
        {
            maze[ghostX4][ghostY4] = previousItem;
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
            ghostY4 = ghostY4 + 1;
            previousItem = maze[ghostX4][ghostY4];
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];

            if (previousItem == 'P')
            {
                maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
        }
    }
    
    if ( value == 3) //move up
    {
        if ( maze[ghostX4 - 1][ghostY4] ==' ' || maze[ghostX4 - 1][ghostY4] == '.' || maze[ghostX4 - 1][ghostY4] == 'P' || maze[ghostX4 - 1][ghostY4] == 'O')
        {
            maze[ghostX4][ghostY4] = previousItem;
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
            ghostX4 = ghostX4 - 1;
            previousItem = maze[ghostX4][ghostY4];
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];

            if (previousItem == 'P')
            {
                maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
        }
    }
    
    if ( value == 4) //move down
    {
        if ( maze[ghostX4 + 1][ghostY4] ==' ' || maze[ghostX4 + 1][ghostY4] == '.' || maze[ghostX4 + 1][ghostY4] == 'P' || maze[ghostX4 + 1][ghostY4] == 'O')
        {
            maze[ghostX4][ghostY4] = previousItem;
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
            ghostX4 = ghostX4 + 1;
            previousItem = maze[ghostX4][ghostY4];
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];

            if (previousItem == 'P')
            {
                maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
            gotoxy( ghostX4, ghostY4);
            cout <<maze[ghostX4][ghostY4];
        }
    }
    return 1;
}

void energy()
{
    for (int i = 0; i < 3000; i++)
    {
        if(ghostX1 > pacX)
        {
            if ( maze[ghostX1 + 1][ghostY1] != '|' && maze[ghostX1 + 1][ghostY1] != '#' && maze[ghostX1 + 1][ghostY1] != '%' )
            {
                maze[ghostX1][ghostY1] = previousItem;
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
                ghostX1 = ghostX1 + 1;
                previousItem = maze[ghostX1][ghostY1];
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];

                maze[ghostX1][ghostY1] = 'G';
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
            }
        }
        if(ghostY1 > pacY)
        {
            if ( maze[ghostX1][ghostY1 + 1] != '|' && maze[ghostX1][ghostY1 + 1] != '#' && maze[ghostX1][ghostY1 + 1] != '%' )
            {
                maze[ghostX1][ghostY1] = previousItem;
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
                ghostY1 = ghostY1 + 1;
                previousItem = maze[ghostX1][ghostY1];
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];

                maze[ghostX1][ghostY1] = 'G';
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
            }
        }
        if(ghostX1 < pacX)
        {
            if ( maze[ghostX1 - 1][ghostY1] != '|' && maze[ghostX1 - 1][ghostY1] != '#' && maze[ghostX1 - 1][ghostY1] != '%' )
            {
                maze[ghostX1][ghostY1] = previousItem;
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
                ghostX1 = ghostX1 - 1;
                previousItem = maze[ghostX1][ghostY1];
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];

                maze[ghostX1][ghostY1] = 'G';
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
            }
        }
        if(ghostY1 < pacY)
        {
            if ( maze[ghostX1][ghostY1 - 1] != '|' && maze[ghostX1][ghostY1 - 1] != '#' && maze[ghostX1][ghostY1 - 1] != '%' )
            {
                maze[ghostX1][ghostY1] = previousItem;
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
                ghostY1 = ghostY1 - 1;
                previousItem = maze[ghostX1][ghostY1];
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];

                maze[ghostX1][ghostY1] = 'G';
                gotoxy( ghostX1, ghostY1);
                cout <<maze[ghostX1][ghostY1];
            }
        }
    }
}
