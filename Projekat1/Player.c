#include "Player.h"
#include "Vectors.h"
#include <stdlib.h>
#include <stdio.h>

Direction currentDirection = RIGHT;
Vector2 playerPos;

void setupPlayer() {
	playerPos.x = 13;
	playerPos.y = 18;

	printf("%d %d", playerPos.x, playerPos.y);
}

void handleInput(char input) {
	switch (input)
	{
	case 'w':
		currentDirection = UP;
		break;
	case 'a':
		currentDirection = LEFT;
		break;
	case 's':
		currentDirection = DOWN;
		break;
	case 'd':
		currentDirection = RIGHT;
		break;
	default:
		break;
	}
}

void movePlayer(char* newPositionAdress) {
	if (*newPositionAdress == '#') {
		return;
	}
}

void getPlayerPos(Vector2** pos) {
	*pos = &playerPos;
}

void setPlayerPos(int x, int y) {
	playerPos.x = x;
	playerPos.y = y;
}

Direction getPlayerDirection() {
	return currentDirection;
}