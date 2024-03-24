#include "Player.h"

typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
}Direction;

Direction currentDirection = RIGHT;

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
	if (newPositionAdress == '#') {
		return;
	}

}