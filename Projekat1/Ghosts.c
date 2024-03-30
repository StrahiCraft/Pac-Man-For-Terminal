#include "Ghosts.h"
#include "Vectors.h"
#include "Map.h"

Vector2 blinkyPos;
Vector2 pinkyPos;
Vector2 inkyPos;
Vector2 clydePos;

Vector2 blinkyPath[8];
Vector2 pinkyPath[8];
Vector2 inkyPath[8];
Vector2 clydePath[8];

void moveBlinky() {

}

void movePinky() {

}

void moveInky() {

}

void moveClyde() {

}

int ghostHere(Vector2 pos) {
	if (pos.x == blinkyPos.x && pos.y == blinkyPos.y) {
		return 1;
	}
	if (pos.x == pinkyPos.x && pos.y == pinkyPos.y) {
		return 2;
	}
	if (pos.x == inkyPos.x && pos.y == inkyPos.y) {
		return 3;
	}
	if (pos.x == clydePos.x && pos.y == clydePos.y) {
		return 4;
	}
	return 0;
}

void pathfind(Vector2 startPos, Vector2 endPos, int iteration) {
	if (iteration == 8) {
		return;
	}

	// UP
	if (getCell(startPos.x, startPos.y - 1) != '#') {

	}
	// DOWN
	if (getCell(startPos.x, startPos.y + 1) != '#') {

	}
	// LEFT
	if (getCell(startPos.x - 1, startPos.y) != '#') {

	}
	// RIGHT
	if (getCell(startPos.x + 1, startPos.y) != '#') {

	}
}