#include <windows.h>
#include "Libreria.h"

void Gotoxy( int x, int y ) 
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y }; 
	SetConsoleCursorPosition( hStdout, position );
	return;
};

void Esperar(int t)
{
	Sleep(t);
	return;
}
