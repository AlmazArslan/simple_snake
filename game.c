#include "game.h"

tSnakeGame* CreateGame(HANDLE hStdout, int w, int h)
{
	int i, j;
	tSnakeGame* newGame;

	i = 0;
	newGame = (tSnakeGame *)(malloc(sizeof(tSnakeGame)));

	newGame->map = (char **)(malloc(h * sizeof(char *)));
	while (i < h)
	{
		newGame->map[i] = (char *)(malloc(w));
		j = 0;
		while (j < w)
		{
			newGame->map[i][j] = 0;
			j++;
		}
		i++;
	}
	newGame->snake = (tCoord *)(malloc(sizeof(tCoord)));
	newGame->snake->x = w / 2;
	newGame->snake->y = h / 2;
	newGame->snake->next = NULL;
	newGame->turn = 0;
	newGame->width = w;
	newGame->height = h;
	newGame->hStdout = hStdout;
	newGame->state = 1;
	newGame->apples = NULL;

	return (newGame);
}

void freeApples(tApple *a)
{
	tApple *temp;

	while (a)
	{
		temp = a->next;
		free(a);
		a = temp;
	}
}

void freeSnake(tCoord *snake)
{
	tCoord *temp;

	while (snake)
	{
		temp = snake->next;
		free(snake);
		snake = temp;
	}
}

void DelGame(tSnakeGame *g)
{
	int i;

	i = 0;
	while (i < g->height)
		free(g->map[i++]);
	free(g->map);

	freeSnake(g->snake);

	freeApples(g->apples);
}

void AddApple(tSnakeGame *g, int x, int y)
{
	tApple *newApple, *temp;
	newApple = (tApple *)(malloc(sizeof(tApple)));
	newApple->x = x;
	newApple->y = y;
	newApple->next = NULL;
	if (!g->apples)
	{
		g->apples = newApple;
		return;
	}
	temp = g->apples;
	while (temp->next)
		temp = temp->next;
	temp->next = newApple;
}

void ShowGame(tSnakeGame *g)
{
	int i, j;
	char c;
	tCoord *tempCoord;
	tApple *temp;

	// Border
	i = 0;
	while (i <= g->height + 1)
	{
		j = 0;
		while (j <= g->width + 1)
		{
			if (i == 0 || j == 0
				|| i == g->height + 1 || j == g->width + 1)
			{
				goTo(g->hStdout, j, i);
				WriteConsole(g->hStdout, "#", 1, NULL, NULL);
			}
			j++;
		}
		i++;
	}

	// Map clean
	i = 0;
	while (i < g->height)
	{
		goTo(g->hStdout, 1, i + 1);
		WriteConsole(g->hStdout, g->map[i], g->width, NULL, NULL);
		i++;
	}

	// Apples
	temp = g->apples;
	while (temp)
	{
		goTo(g->hStdout, temp->x + 1, temp->y + 1);
		WriteConsole(g->hStdout, "*", 1, NULL, NULL);
		temp = temp->next;
	}

	// Snake
	c = '0';
	tempCoord = g->snake;
	while (tempCoord)
	{
		goTo(g->hStdout, tempCoord->x, tempCoord->y);
		WriteConsole(g->hStdout, &c, 1, NULL, NULL);
		c = '+';
		tempCoord = tempCoord->next;
	}
}

void MoveSnake(tSnakeGame *g, char delLast)
{
	tCoord *newHead, *temp;

	temp = g->snake;
	newHead = (tCoord *)(malloc(sizeof(tCoord)));
	newHead->x = temp->x;
	newHead->y = temp->y;
	newHead->next = temp;
	switch (g->turn)
	{
		case 0:
			newHead->y--;
			break;
		case 1:
			newHead->x++;
			break;
		case 2:
			newHead->y++;
			break;
		case 3:
			newHead->x--;
			break;
	}
	g->snake = newHead;
	if (!delLast)
		return;

	temp = newHead;
	while (temp->next->next)
		temp = temp->next;
	free(temp->next);
	temp->next = NULL;
}

DWORD WINAPI updateTurn(void *gg)
{
	tSnakeGame *g = (tSnakeGame *)gg;
	while (1 == 1)
	{
		if (GetKeyState('W') & 0x8000 && g->turn != 2)
			g->turn = 0;
		if (GetKeyState('D') & 0x8000 && g->turn != 3)
			g->turn = 1;
		if (GetKeyState('S') & 0x8000 && g->turn != 0)
			g->turn = 2;
		if (GetKeyState('A') & 0x8000 && g->turn != 1)
			g->turn = 3;
		// Sleep();
	}
}

void StartGameLoop(tSnakeGame *g)
{
	AddApple(g, 0, 0);
	AddApple(g, 5, 2);
	AddApple(g, 30, 3);
	AddApple(g, 10, 6);
	ShowGame(g);
	CreateThread(NULL, 0, updateTurn, g, 0, NULL);
	while (1)
	{
		ShowGame(g);
		MoveSnake(g, true);
		Sleep(400);
	}
}