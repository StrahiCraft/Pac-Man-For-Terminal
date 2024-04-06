#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

#include "Player.h"
#include "Render.h"
#include "Map.h"
#include "Ghosts.h"

int main() {
	int input = 0;
	setupPlayer();

	loadMap("map.txt");
	setupMap();

	while (input != 'q' && input != 27)
	{
		if (kbhit()) {
			input = getch();
		}
		handleInput(input);
		movePlayer();
		changeDirection(getNextDirection());

		moveBlinky();

		renderGame();

		Sleep(200);
		system("cls");
	}
	return 0;
}