#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>

#include "Player.h"
#include "Render.h"
#include "Map.h"
#include "Ghosts.h"

int ghostMovement = 0;

int ghostCheck() {
	if (isGhostHere(getPlayerPos().x, getPlayerPos().y)) {
		if (isGhostFrightened(isGhostHere(getPlayerPos().x, getPlayerPos().y))) {
			eatGhost(isGhostHere(getPlayerPos().x, getPlayerPos().y));
			Sleep(200);
		}
		else {
			return 1;
		}
	}
	return 0;
}

int main() {
	srand(time(NULL));
	int input = 0;

	loadMap("map.txt");
	setupMap();

	while (input != 'q' && input != 27)
	{
		if (ghostCheck()) {
			break;
		}
		if (kbhit()) {
			input = getch();
		}
		handleInput(input);
		movePlayer();
		changeDirection(getNextDirection());

		if (ghostCheck()) {
			break;
		}
		moveBlinky();
		movePinky();

		moveClyde();

		if (ghostCheck()) {
			break;
		}

		renderGame();

		ghostMovement++;
		ghostMovement %= 4;
		Sleep(200);
		system("cls");
	}
	return 0;
}