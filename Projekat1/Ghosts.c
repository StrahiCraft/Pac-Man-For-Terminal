#include "Ghosts.h"
#include "Vectors.h"
#include "Map.h"
#include "Player.h"
#include "Queue.h"

#include <stdio.h>
#include <stdlib.h>

Vector2 blinkyPos;
Vector2 pinkyPos;
Vector2 inkyPos;
Vector2 clydePos;

Vector2 ghostSpawns[4];

Vector2* blinkyPath;
int movementIndex = -1;

ExploredTile* exploredTiles;

int exploredTilesIndex = 0;

void setupGhost(int ghostId, int x, int y) {
	switch (ghostId)
	{
	case 1:
		blinkyPos.x = x;
		blinkyPos.y = y;
		blinkyPath = (Vector2*)calloc(0, sizeof(Vector2));
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
	if (movementIndex != -1 && distance(blinkyPos, getPlayerPos()) < distance(getPlayerPos(), blinkyPath[0])) {
		movementIndex = 0;
	}
	if (movementIndex < 0) {
		refreshExploredTiles();
		free(blinkyPath);
		blinkyPath = (Vector2*)calloc(getHeight() * getWidth(), sizeof(Vector2));
		movementIndex = pathfind(blinkyPos, getPlayerPos(), blinkyPath) - 1;
	}
	blinkyPos = *(blinkyPath + movementIndex--);
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
	exploredTilesIndex = 0;
	clearQueue();
	free(exploredTiles);
	int maxTileCount = getHeight() * getWidth();
	exploredTiles = (ExploredTile*)calloc(maxTileCount, sizeof(ExploredTile));
}

int isTileExplored(Vector2 tile) {
	for (int i = 0; i < exploredTilesIndex; i++) {
 		if (tile.x == exploredTiles[i].position.x && tile.y == exploredTiles[i].position.y) {
			return 1;
		}
	}
	return 0;
}

int getTileAdress(Vector2 pos) {
	for (int i = 0; i < exploredTilesIndex; i++) {
		if (pos.x == exploredTiles[i].position.x && pos.y == exploredTiles[i].position.y) {
			return i;
		}
	}
	return 0;
}

int pathfind(Vector2 startPos, Vector2 endPos, Vector2* ghostPath) {
	enqueue(startPos);
	exploredTiles[exploredTilesIndex++].position = startPos;
	while (getQueueLength() > 0)
	{
		Vector2 newPos = dequeue();
		ExploredTile* currentTile = &exploredTiles[getTileAdress(newPos)];

		if (newPos.x == endPos.x && newPos.y == endPos.y) {
			break;
		}

		newPos.y--;
		if (explore(newPos, endPos, currentTile)) {
			break;
		}
		newPos.y += 2;
		if (explore(newPos, endPos, currentTile)) {
			break;
		}
		newPos.y--;
		newPos.x--;
		if (explore(newPos, endPos, currentTile)) {
			break;
		}
		newPos.x += 2;
		if (explore(newPos, endPos, currentTile)) {
			break;
		}
	}
	ExploredTile* currentTile = &exploredTiles[exploredTilesIndex - 1];
	int iteration = 0;
	while (currentTile->origin != NULL)
	{
		ghostPath[iteration++] = currentTile->position;
		currentTile = currentTile->origin;
	}
	return iteration;
}

int explore(Vector2 newPos, Vector2 endPos, ExploredTile* origin) {
	if (getCell(newPos.x, newPos.y) == '#') {
		return 0;
	}
	if (isTileExplored(newPos)) {
		return 0;
	}

	if (newPos.y < 0) {
		newPos.y = getHeight() - 2;
	}
	if (newPos.x < 0) {
		newPos.x = getWidth() - 2;
	}

	newPos.y %= getHeight() - 1;
	newPos.x %= getWidth() - 1;

	exploredTiles[exploredTilesIndex].position = newPos;
	exploredTiles[exploredTilesIndex].origin = origin;
	exploredTilesIndex++;

	if (newPos.x == endPos.x && newPos.y == endPos.y) {
		return 1;
	}

	enqueue(newPos);

	return 0;
}