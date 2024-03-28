#ifndef PLAYER_H_
#define PLAYER_H_
#include "Vectors.h"

typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
}Direction;

void setupPlayer();
void handleInput(char input);
void movePlayer();
int isPlayerHere(int x, int y);
void setPlayerPos(int x, int y);
Direction getPlayerDirection();

#endif

