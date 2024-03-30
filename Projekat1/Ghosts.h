#ifndef GHOSTS_H_
#define GHOSTS_H_
#include "Vectors.h"

typedef enum GhostMode {
	CHASE,
	SCATTER,
	FRIGHTENED
}GhostMode;

void setupGhost(int ghostId, int x, int y);

void moveBlinky();
void movePinky();
void moveInky();
void moveClyde();

int isGhostHere(int x, int y);
void refreshExploredTiles();
int isTileExplored(Vector2 tile);
void pathfind(Vector2 startPos, Vector2 endPos, int iteration, Vector2* ghostPath);

Vector2 getPos();
#endif // !GHOSTS_H_
