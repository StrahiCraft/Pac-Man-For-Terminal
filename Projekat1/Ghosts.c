#include "Ghosts.h"
#include "Vectors.h"
#include "Map.h"
#include "Player.h"

#include <stdlib.h>

Vector2 blinkyPos;
Vector2 pinkyPos;
Vector2 inkyPos;
Vector2 clydePos;

Vector2 ghostSpawns[4];

Vector2 blinkyPath[16];
int blinkyPathToPacDistance;
int blinkyCanMove = 0;
Vector2 pinkyPath[16];
Vector2 inkyPath[16];
Vector2 clydePath[16];
int movementIndex = 0;

Vector2 currentPath[16];
Vector2 *exploredTiles;
int exploredTilesIndex = 0;
int bestPathLength = 2147483647;

void setupGhost(int ghostId, int x, int y) {
	switch (ghostId)
	{
	case 1:
		blinkyPos.x = x;
		blinkyPos.y = y;
		break;
	case 2:
		pinkyPos.x = x;
		pinkyPos.y = y;
		break;
	case 3:
		inkyPos.x = x;
		inkyPos.y = y;
		break;
	case 4:
		clydePos.x = x;
		clydePos.y = y;
		break;
	default:
		return;
	}
	ghostSpawns[ghostId - 1].x = x;
	ghostSpawns[ghostId - 1].y = y;
}

void moveBlinky() {
	if (movementIndex == 16) {
		bestPathLength = 2147483647;
		Vector2 playerPos = getPlayerPos();
		pathfind(blinkyPos, playerPos, 0, blinkyPath);
		movementIndex = 0;
		blinkyCanMove = 1;
	}
	if (!blinkyCanMove) {
		movementIndex++;
		return;
	}
	blinkyPos = blinkyPath[movementIndex++];
}

Vector2 getPos() {
	return blinkyPos;
}

void movePinky() {

}

void moveInky() {

}

void moveClyde() {

}

int isGhostHere(int x, int y) {
	if (x == blinkyPos.x && y == blinkyPos.y) {
		return 1;
	}
	if (x == pinkyPos.x && y == pinkyPos.y) {
		return 2;
	}
	if (x == inkyPos.x && y == inkyPos.y) {
		return 3;
	}
	if (x == clydePos.x && y == clydePos.y) {
		return 4;
	}
	return 0;
}

void refreshExploredTiles() {
	free(exploredTiles);
	exploredTiles = (Vector2*)malloc(576);
}

int isTileExplored(Vector2 tile) {
	for (int i = 0; i < 576; i++) {
		if (tile.x == (exploredTiles + i)->x && tile.y == (exploredTiles + i)->y) {
			return 1;
		}
	}
	return 0;
}

void pathfind(Vector2 startPos, Vector2 endPos, int iteration, Vector2* ghostPath) {
	if (iteration == 16 || (startPos.x == endPos.x && startPos.y == endPos.y)) {
		if (distance(startPos, endPos) < bestPathLength) {
			bestPathLength = distance(startPos, endPos);
			for (int i = 0; i < 16; i++){
				*(ghostPath + i) = currentPath[i];
			}
		}
		return;
	}

	/*if (isTileExplored(startPos)) {
		return;
	}*/

	Vector2 newPos = startPos;
	// UP
	if (getCell(startPos.x, startPos.y - 1) != '#') {
		newPos.y = startPos.y - 1;
		if (newPos.y < 0) {
			newPos.y = getHeight() - 2;
		}
		currentPath[iteration] = newPos;
		pathfind(newPos, endPos, iteration + 1, ghostPath);
	}
	// DOWN
	if (getCell(startPos.x, startPos.y + 1) != '#') {
		newPos.y = startPos.y + 1;
		newPos.y %= getHeight() - 1;
		currentPath[iteration] = newPos;
		pathfind(newPos, endPos, iteration + 1, ghostPath);
	}
	newPos.y = startPos.y;
	// LEFT
	if (getCell(startPos.x - 1, startPos.y) != '#') {
		newPos.x = startPos.x - 1;
		if (newPos.x < 0) {
			newPos.x = getWidth() - 2;
		}
		currentPath[iteration] = newPos;
		pathfind(newPos, endPos, iteration + 1, ghostPath);
	}
	// RIGHT
	if (getCell(startPos.x + 1, startPos.y) != '#') {
		newPos.x = startPos.x + 1;
		newPos.x %= getWidth() - 1;
		currentPath[iteration] = newPos;
		pathfind(newPos, endPos, iteration + 1, ghostPath);
	}
}