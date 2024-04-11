#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>

#include "Player.h"
#include "Render.h"
#include "Map.h"
#include "Ghosts.h"
#include "MainMenu.h"

void menuLoop();
void gameLoop();

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

void gameLoop() {
	int input = 0;

	//loadMap("map.txt");
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
		moveInky();
		moveClyde();

		renderGame();

		if (ghostCheck()) {
			system("cls");
			printf("GAME OVER!");
			Sleep(2000);
			break;
		}

		if (getPelletCount() == 0) {
			system("cls");
			printf("You won!");
			Sleep(3000);
			break;
		}

		Sleep(200);
		system("cls");
	}
	
	system("cls");
}

void menuLoop() {
	int exitCode = 0;
	while (1) {
		renderLogo();

		renderButtons();
		printf(CYAN"\n\n\n Game by: Strahinja Nikolic"RESET_COLOR);
		exitCode = navigateMenu(getch());
		system("cls");
		char mapName[50];
		switch (exitCode)
		{
		case 1:
			printf("Enter map name: ");
			gets_s(mapName, 50);
			if (loadMap(mapName)) {
				system("cls");
				printf(RED "ERROR! MAP NOT FOUND!\n" RESET_COLOR);
				break;
			}
			gameLoop();
			break;
		case 2:
			
			break;
		case 3:
			// exit game
			return;
		default:
			break;
		}
	}
}

int main() {
	srand(time(NULL));
	
	menuLoop();
	
	return 0;
}