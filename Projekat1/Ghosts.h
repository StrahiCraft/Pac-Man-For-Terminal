#ifndef GHOSTS_H_
#define GHOSTS_H_
#include "Vectors.h"

typedef enum GhostMode {
	CHASE,
	SCATTER,
	FRIGHTENED
}GhostMode;

typedef struct ExploredTile {
	Vector2 position;
	struct ExploredTile* origin;
}ExploredTile;

void setupGhost(int ghostId, int x, int y);

void moveBlinky();
void movePinky();
void moveInky();
void moveClyde();

void frightenGhosts();
int isGhostHere(int x, int y);
int isGhostFrightened(int ghostId);

void refreshExploredTiles();

int isTileExplored(Vector2 tile);
int getTileAdress(Vector2 pos);
int pathfind(Vector2 startPos, Vector2 endPos, Vector2* ghostPath);
int explore(Vector2 newPos, Vector2 endPos, ExploredTile* origin);

#endif // !GHOSTS_H_
