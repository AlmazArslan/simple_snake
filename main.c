#include "main.h"

int main()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	tSnakeGame *game = CreateGame(hStdout, 60, 20);
	StartGameLoop(game);
	DelGame(game);

	return (0);
}