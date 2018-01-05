/* Helper functions to make it work on Win32 without changes to the main source code */
#include <windows.h>
#include <time.h>

HANDLE handle;
COORD cr;

inline void gotoxy(int x_coord, int y_coord)
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cr.X = (short)x_coord;
    cr.Y = (short)y_coord;

    SetConsoleCursorPosition(handle, cr);
}

/*
void textcolor(int a)
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}
*/

inline void clrscr(void)
{
    system("cls");
}

inline int random(int number)
{
    return ((rand() * number) / (RAND_MAX + 1));
    // return (rand() % number);
}

inline void randomize(void)
{
    srand(time(NULL));
}
