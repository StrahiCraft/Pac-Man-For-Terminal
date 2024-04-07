#ifndef PLAYER_H_
#define PLAYER_H_
#include "Vectors.h"

typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
}Direction;

void setupPlayer(int x, int y);
void handleInput(char input);
void changeDirection(Direction dir);
void movePlayer();
Vector2 getPlayerPos();
void setPlayerPos(int x, int y);
Direction getPlayerDirection();
Direction getNextDirection();
int isPlayerHere(int x, int y);

#endif

