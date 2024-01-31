#include "main.h"

void goTo(HANDLE h, int x, int y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(h, pos);
}