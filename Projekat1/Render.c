#include "Render.h"
#include "Vectors.h"
#include "Player.h"
#include "Map.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// colors
#define RESET_COLOR   "\x1b[0m"

#define BLUE "\x1b[34m"
#define WHITE "\x1b[97m"
#define YELLOW "\x1b[93m"

Vector2 mapDimensions;

void setupMap() {
	mapDimensions.x = getWidth();
	mapDimensions.y = getHeight();
}

void renderGame() {
	printf(" ");
	for (int y = 0; y < mapDimensions.y; y++) {
		for (int x = 0; x < mapDimensions.x; x++) {
			
			if (isPlayerHere(x, y)) {
				renderPlayer(getPlayerDirection());
				x++;
				if (x >= mapDimensions.x) {
					break;
				}
			}

			switch (getCell(x, y))
			{
			case '#':
				printf(BLUE "# " RESET_COLOR);
				break;
			case '.':
				printf(WHITE ". " RESET_COLOR);
				break;
			default:
				printf(WHITE "%c " RESET_COLOR, getCell(x, y));
				break;
			}
		}
	}
}

void renderPlayer(Direction direction) {
	switch (direction)
	{
	case UP:
		printf(YELLOW "U " RESET_COLOR);
		break;
	case DOWN:
		printf(YELLOW "n " RESET_COLOR);
		break;
	case LEFT:
		printf(YELLOW "> " RESET_COLOR);
		break;
	case RIGHT:
		printf(YELLOW "C " RESET_COLOR);
		break;
	default:
		break;
	}
}

void renderGhost(Vector2 position, int ghostId) {

}