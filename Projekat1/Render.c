#include "Render.h"
#include "Vectors.h"
#include "Player.h"
#include "Map.h"
#include "Ghosts.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


Vector2 mapDimensions;
int ghostFlash = 0;

void setupMap() {
	mapDimensions.x = getWidth();
	mapDimensions.y = getHeight();
}

void renderGame() {
	printf(" ");
	for (int y = 0; y < mapDimensions.y; y++) {
		for (int x = 0; x < mapDimensions.x; x++) {
			ghostFlash = !ghostFlash;
			if (isPlayerHere(x, y)) {
				renderPlayer(getPlayerDirection());
				x++;
				if (x >= mapDimensions.x) {
					break;
				}
			}

			if (isGhostHere(x, y)) {
				renderGhost(isGhostHere(x, y));
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
			case 'G':
				printf("  ");
				break;
			case 'P':
				printf("  ");
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

void renderGhost(int ghostId) {
	if (isGhostFrightened(ghostId)) {
		if (ghostFlash) {
			printf(BRIGHT_BLUE "M " RESET_COLOR);
			return;
		}
		printf(GRAY "M " RESET_COLOR);
		return;
	}
	switch (ghostId)
	{
	case 1:
		printf(RED "M " RESET_COLOR);
		break;
	case 2:
		printf(PINK "M " RESET_COLOR);
		break;
	case 3:
		printf(CYAN "M " RESET_COLOR);
		break;
	case 4:
		printf(ORANGE "M " RESET_COLOR);
		break;
	default:
		break;
	}
}