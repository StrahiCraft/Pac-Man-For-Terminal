#include "Player.h"
#include "Vectors.h"
#include "Map.h"
#include "Ghosts.h"

#include <stdlib.h>
#include <stdio.h>

Direction currentDirection = RIGHT;
Direction nextDirection = RIGHT;
Vector2 playerPos;

void setupPlayer(int x, int y) {
	playerPos.x = x;
	playerPos.y = y;
}

void handleInput(char input) {
	switch (input)
	{
	case 'w':
		changeDirection(UP);
		break;
	case 'a':
		changeDirection(LEFT);
		break;
	case 's':
		changeDirection(DOWN);
		break;
	case 'd':
		changeDirection(RIGHT);
		break;
	default:
		break;
	}
}

void changeDirection(Direction dir) {
	switch (dir)
	{
	case UP:
		if (getCell(playerPos.x, playerPos.y - 1) == '#' ||
			getCell(playerPos.x, playerPos.y - 1) == '_') {
			nextDirection = dir;
			return;
		}
		break;
	case DOWN:
		if (getCell(playerPos.x, playerPos.y + 1) == '#' ||
			getCell(playerPos.x, playerPos.y + 1) == '_') {
			nextDirection = dir;
			return;
		}
		break;
	case LEFT:
		if (getCell(playerPos.x - 1, playerPos.y) == '#' ||
			getCell(playerPos.x - 1, playerPos.y) == '_') {
			nextDirection = dir;
			return;
		}
		break;
	case RIGHT:
		if (getCell(playerPos.x + 1, playerPos.y) == '#' ||
			getCell(playerPos.x + 1, playerPos.y) == '_') {
			nextDirection = dir;
			return;
		}
		break;
	default:
		break;
	}
	currentDirection = dir;
	nextDirection = currentDirection;
}

void movePlayer() {
	switch (currentDirection)
	{
	case UP:
		if (getCell(playerPos.x, playerPos.y - 1) == '#' ||
			getCell(playerPos.x, playerPos.y - 1) == '_') {
			return;
		}
		playerPos.y--;
		break;
	case DOWN:
		if (getCell(playerPos.x, playerPos.y + 1) == '#' ||
			getCell(playerPos.x, playerPos.y + 1) == '_') {
			return;
		}
		playerPos.y++;
		break;
	case LEFT:
		if (getCell(playerPos.x - 1, playerPos.y) == '#' ||
			getCell(playerPos.x - 1, playerPos.y) == '_') {
			return;
		}
		playerPos.x--;
		break;
	case RIGHT:
		if (getCell(playerPos.x + 1, playerPos.y) == '#' || 
			getCell(playerPos.x + 1, playerPos.y) == '_') {
			return;
		}
		playerPos.x++;
		break;
	default:
		break;
	}

	if (playerPos.x < 0) {
		playerPos.x = getWidth() - 2;
	}

	if (playerPos.y < 0) {
		playerPos.y = getHeight() - 2;
	}


	playerPos.x %= getWidth() - 1;
	playerPos.y %= getHeight() - 1;

	if (getCell(playerPos.x, playerPos.y) == '.') {
		setCell(playerPos.x, playerPos.y);
		
		collectPellet();
	}

	if (getCell(playerPos.x, playerPos.y) == 'o') {
		setCell(playerPos.x, playerPos.y);
		
		frightenGhosts();
	}
}

Vector2 getPlayerPos() {
	return playerPos;
}

void setPlayerPos(int x, int y) {
	playerPos.x = x;
	playerPos.y = y;
}

Direction getPlayerDirection() {
	return currentDirection;
}

Direction getNextDirection() {
	return nextDirection;
}

int isPlayerHere(int x, int y) {
	return x == playerPos.x && y == playerPos.y;
}