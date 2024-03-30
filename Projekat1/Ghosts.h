#ifndef GHOSTS_H_
#define GHOSTS_H_
#include "Vectors.h"

typedef enum GhostMode {
	CHASE,
	SCATTER,
	FRIGHTENED
}GhostMode;

void moveBlinky();
void movePinky();
void moveInky();
void moveClyde();

int ghostHere(Vector2 pos);
void pathfind(Vector2 startPos, Vector2 endPos, int iteration);

#endif // !GHOSTS_H_
