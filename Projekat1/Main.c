#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

#include "Player.h"
#include "Render.h"

int main() {
	int input = 0;
	setupPlayer();

	while (input != 'q' && input != 27)
	{
		if (kbhit()) {
			input = getch();
		}
		handleInput(input);
		movePlayer();

		renderGame();

		Sleep(200);
		system("cls");
	}
	return 0;
}