#include "Ghosts.h"
#include "Vectors.h"
#include "Map.h"
#include "Player.h"
#include "Queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vector2 ghostSpawns[4];

Vector2 blinkyPos;
Vector2 pinkyPos;
Vector2 inkyPos;
Vector2 clydePos;

Vector2* blinkyPath;
Vector2* pinkyPath;
Vector2* inkyPath;
Vector2* clydePath;

int blinkyMovementIndex = -1;
int pinkyMovementIndex  = -1;
int inkyMovementIndex   = -1;
int clydeMovementIndex  = -1;

GhostMode blinkyMode = SCATTER;
GhostMode pinkyMode  = SCATTER;
GhostMode inkyMode   = SCATTER;
GhostMode clydeMode  = SCATTER;

ExploredTile* exploredTiles;

int exploredTilesIndex = 0;

int ghostMovement = 0;

// ========================================================================
// GHOST MOVEMENT SECTION
// ========================================================================

void moveBlinky() {
	Vector2 endPos = getPlayerPos();

	if (blinkyMode == SCATTER && blinkyMovementIndex == -1) {
		endPos.x = rand() % getWidth();
		endPos.y = rand() % getHeight();
		blinkyMovementIndex = 0;
	}

	if (blinkyMode == FRIGHTENED) {
		endPos = ghostSpawns[0];
		blinkyMovementIndex = 0;
	}

	if (blinkyMode == CHASE && distance(blinkyPos, getPlayerPos()) < distance(getPlayerPos(), blinkyPath[0])) {
		blinkyMovementIndex = 0;
	}
	if (blinkyMovementIndex < 1) {
		refreshExploredTiles();
		free(blinkyPath);
		blinkyPath = (Vector2*)calloc(getHeight() * getWidth(), sizeof(Vector2));
		blinkyMovementIndex = pathfind(blinkyPos, endPos, blinkyPath) - 1;
	}
	moveGhost(&blinkyPos, blinkyPath, &blinkyMovementIndex, blinkyMode);
	if (blinkyMovementIndex <= 0) {
		if (blinkyMode == FRIGHTENED) {
			blinkyMode = SCATTER;
			blinkyMovementIndex = -1;
			return;
		}
		if (blinkyMode == SCATTER) {
			blinkyMode = CHASE;
		}
	}
}

void movePinky() {
	Vector2 endPos = getPlayerPos();

	if (pinkyMode == SCATTER && pinkyMovementIndex == -1) {
		endPos.x = rand() % getWidth();
		endPos.y = rand() % getHeight();
		pinkyMovementIndex = 0;
	}

	if (pinkyMode == FRIGHTENED) {
		endPos = ghostSpawns[1];
		pinkyMovementIndex = 0;
	}

	if (pinkyMode == CHASE) {
		switch (getPlayerDirection())
		{
		case UP:
			offsetPosition(&endPos, 0, -4);
			break;
		case DOWN:
			offsetPosition(&endPos, 0, 4);
			break;
		case LEFT:
			offsetPosition(&endPos, -4, 0);
			break;
		case RIGHT:
			offsetPosition(&endPos, 4, 0);
			break;
		default:
			break;
		}
	}
	if (pinkyMovementIndex < 1) {
		refreshExploredTiles();
		free(pinkyPath);
		pinkyPath = (Vector2*)calloc(getHeight() * getWidth(), sizeof(Vector2));
		pinkyMovementIndex = pathfind(pinkyPos, endPos, pinkyPath) - 1;
	}
	moveGhost(&pinkyPos, pinkyPath, &pinkyMovementIndex, pinkyMode);

	if (pinkyPos.x == endPos.x && pinkyPos.y == endPos.y) {
		if (pinkyMode == FRIGHTENED) {
			pinkyMode = SCATTER;
			pinkyMovementIndex = -1;
			return;
		}
		if (pinkyMode == SCATTER) {
			pinkyMode = CHASE;
			return;
		}
		if (pinkyMode == CHASE && distance(pinkyPos, getPlayerPos()) > 15) {
			pinkyMode = SCATTER;
			pinkyMovementIndex = -1;
		}
	}
}

void moveInky() {
	Vector2 endPos = getPlayerPos();

	if (inkyMode == SCATTER && inkyMovementIndex == -1) {
		endPos.x = rand() % getWidth();
		endPos.y = rand() % getHeight();
		inkyMovementIndex = 0;
	}

	if (inkyMode == FRIGHTENED) {
		endPos = ghostSpawns[2];
		inkyMovementIndex = 0;
	}

	if (inkyMode == CHASE && inkyMovementIndex == -1) {
		Vector2 offset = getOffset(blinkyPos, getPlayerPos());
		offsetPosition(&endPos, offset.x * 2, offset.y * 2);
		inkyMovementIndex = 0;
	}

	if (inkyMovementIndex < 1) {
		refreshExploredTiles();
		free(inkyPath);
		inkyPath = (Vector2*)calloc(getHeight() * getWidth(), sizeof(Vector2));
		inkyMovementIndex = pathfind(inkyPos, endPos, inkyPath) - 1;
		
	}
	moveGhost(&inkyPos, inkyPath, &inkyMovementIndex, inkyMode);
	if (inkyPos.x == endPos.x && inkyPos.y == endPos.y) {
		if (inkyMode == FRIGHTENED) {
			inkyMode = SCATTER;
			inkyMovementIndex = -1;
			return;
		}
		if (inkyMode == SCATTER) {
			inkyMode = CHASE;
			inkyMovementIndex = -1;
		}
	}
}

void moveClyde() {
	Vector2 endPos = getPlayerPos();

	if (distance(clydePos, getPlayerPos()) > 8 && clydeMode != FRIGHTENED) {
		clydeMode = SCATTER;
		clydeMovementIndex = -1;
	}

	if (clydeMode == SCATTER && clydeMovementIndex == -1) {
		endPos.x = rand() % getWidth();
		endPos.y = rand() % getHeight();
		clydeMovementIndex = 0;
	}

	if (clydeMode == FRIGHTENED) {
		endPos = ghostSpawns[3];
		clydeMovementIndex = 0;
	}

	if (clydeMode == SCATTER && distance(clydePos, getPlayerPos()) < 9) {
		endPos = getPlayerPos();
		clydeMovementIndex = 0;
		clydeMode = CHASE;
	}
	if (clydeMovementIndex < 1) {
		refreshExploredTiles();
		free(clydePath);
		clydePath = (Vector2*)calloc(getHeight() * getWidth(), sizeof(Vector2));
		clydeMovementIndex = pathfind(clydePos, endPos, clydePath) - 1;
	}
	moveGhost(&clydePos, clydePath, &clydeMovementIndex, clydeMode);
	ghostMovement++;
	if (clydePos.x == endPos.x && clydePos.y == endPos.y) {
		if (clydeMode == FRIGHTENED) {
			clydeMode = SCATTER;
			clydeMovementIndex = -1;
			return;
		}
		if (clydeMode == SCATTER) {
			clydeMode = CHASE;
			return;
		}
	}
}

void moveGhost(Vector2* ghostPos, Vector2* ghostPath, int* ghostMovementIndex, GhostMode ghostMode) {
	switch (ghostMode)
	{
	case SCATTER:
		if (ghostMovement % 3 == 2 || ghostMovement % 3 == 1) {
			break;
		}
		return;
	case FRIGHTENED:
		if (ghostMovement % 2 == 0) {
			break;
		}
		return;
	default:
		break;
	}
	*ghostPos = *(ghostPath + *ghostMovementIndex);
	*ghostMovementIndex -= 1;
}

// ========================================================================
// GHOST MANAGEMENT SECTION
// ========================================================================

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
		pinkyPath = (Vector2*)calloc(0, sizeof(Vector2));
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

void frightenGhosts() {
	blinkyMode = FRIGHTENED;
	pinkyMode  = FRIGHTENED;
	inkyMode   = FRIGHTENED;
	clydeMode  = FRIGHTENED;
}

int isGhostFrightened(int ghostId) {
	switch (ghostId)
	{
	case 1:
		return blinkyMode == FRIGHTENED;
	case 2:
		return pinkyMode == FRIGHTENED;
	case 3:
		return inkyMode == FRIGHTENED;
	case 4:
		return clydeMode == FRIGHTENED;
	default:
		return 0;
	}
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

void eatGhost(int ghostId) {
	switch (ghostId)
	{
	case 1:
		blinkyPos = ghostSpawns[0];
		blinkyMovementIndex = 0;
		blinkyMode = SCATTER;
		break;
	case 2:
		pinkyPos = ghostSpawns[1];
		pinkyMovementIndex = 0;
		pinkyMode = SCATTER;
		break;
	case 3:
		inkyPos = ghostSpawns[2];
		inkyMovementIndex = 0;
		inkyMode = SCATTER;
		break;
	case 4:
		clydePos = ghostSpawns[3];
		clydeMovementIndex = 0;
		clydeMode = SCATTER;
		break;
	default:
		break;
	}
}

// ========================================================================
// MEMORY MANAGEMENT SECTION
// ========================================================================

void refreshExploredTiles() {
	exploredTilesIndex = 0;
	clearQueue();
	free(exploredTiles);
	int maxTileCount = getHeight() * getWidth();
	exploredTiles = (ExploredTile*)calloc(maxTileCount, sizeof(ExploredTile));
}

// ========================================================================
// EXPLORED TILE MANAGEMENT SECTION
// ========================================================================

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

int findClosestValidTile(Vector2 tile) {
	int bestDistance = distance(tile, exploredTiles[0].position);
	int bestDistanceIndex = 0;
	for (int i = 1; i < exploredTilesIndex; i++) {
		if (bestDistance > distance(tile, exploredTiles[i].position)) {
			bestDistance = distance(tile, exploredTiles[i].position);
			bestDistanceIndex = i;
		}
	}
	return bestDistanceIndex;
}

// ========================================================================
// PATHFINDING SECTION
// ========================================================================

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

	if (currentTile->position.x != endPos.x || currentTile->position.y != endPos.y) {
		currentTile = &exploredTiles[findClosestValidTile(endPos)];
	}

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

	if (isTileExplored(newPos)) {
		return 0;
	}

	exploredTiles[exploredTilesIndex].position = newPos;
	exploredTiles[exploredTilesIndex].origin = origin;
	exploredTilesIndex++;

	if (newPos.x == endPos.x && newPos.y == endPos.y) {
		return 1;
	}

	enqueue(newPos);

	return 0;
}

void offsetPosition(Vector2* pos, int xOffset, int yOffset) {
	pos->x += xOffset;
	pos->y += yOffset;

	if (pos->x < 0) {
		pos->x = 1;
	}

	if (pos->y < 0) {
		pos->y = 1;
	}
	
	if (pos->x > getWidth() - 2) {
		pos->x = getWidth() - 2;
	}

	if (pos->y > getHeight() - 2) {
		pos->y = getHeight() - 2;
	}
}

// ========================================================================