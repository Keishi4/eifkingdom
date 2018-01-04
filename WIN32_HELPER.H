/* Helper functions to make it work on Win32 without changes to the main source code */

#include <windows.h>
#include <time.h>

HANDLE handle;
COORD cr;

void gotoxy(int x_coord, int y_coord)
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cr.X = x_coord;
    cr.Y = y_coord;

    SetConsoleCursorPosition(handle, cr);
}

/*
void textcolor(int a)
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}
*/

void clrscr(void)
{
    system("cls");
}

int random(int number)
{
    return ((rand() * number) / (RAND_MAX + 1));
    // return (rand() % number);
}

void randomize(void)
{
    srand(time(NULL));
}
