#include "Player.h"
#include "Vectors.h"
#include "Render.h"

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

void movePlayer() {
	switch (currentDirection)
	{
	case UP:
		if (getCell(playerPos.x, playerPos.y - 1) == '#') {
			return;
		}
		playerPos.y--;
		break;
	case DOWN:
		if (getCell(playerPos.x, playerPos.y + 1) == '#') {
			return;
		}
		playerPos.y++;
		break;
	case LEFT:
		if (getCell(playerPos.x - 1, playerPos.y) == '#') {
			return;
		}
		playerPos.x--;
		break;
	case RIGHT:
		if (getCell(playerPos.x + 1, playerPos.y) == '#') {
			printf("%c", getCell(playerPos.x, playerPos.y));
			return;
		}
		playerPos.x++;
		break;
	default:
		break;
	}

	if (playerPos.x < 0) {
		playerPos.x = 27;
	}


	playerPos.x %= 28;
	playerPos.y %= 28;

	if (getCell(playerPos.x, playerPos.y) == '.') {
		setCell(playerPos.x, playerPos.y);
		// increase score
	}

	if (getCell(playerPos.x, playerPos.y) == 'o') {
		setCell(playerPos.x, playerPos.y);
		// big strong mode activate
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