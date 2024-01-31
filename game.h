#ifndef GAME_H
#define GAME_H value

#include <stdlib.h>
#include "main.h"

typedef struct sApple
{
	int x;
	int y;
	struct sApple* next;
} tApple;

typedef struct sCoord
{
	int x;
	int y;
	struct sCoord* next;
} tCoord;

typedef struct sSnakeGame
{
	int width;
	int height;
	char state;
	char turn; // 0-UP, 1-Rig, 2-Down, 3-Left
	tCoord* snake;
	HANDLE hStdout;
	char** map;
	tApple* apples;
} tSnakeGame;

tSnakeGame* CreateGame(HANDLE he, int w, int h);
void DelGame(tSnakeGame *g);

void ShowGame(tSnakeGame *g);
void AddApple(tSnakeGame *g, int x, int y);
void StartGameLoop(tSnakeGame *g);

#endif