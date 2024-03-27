#include "Render.h"
#include "Vectors.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// colors
#define RESET_COLOR   "\x1b[0m"

#define BLUE "\x1b[34m"
#define WHITE "\x1b[97m"
#define YELLOW "\x1b[93m"

// the map is 29 wide and 29 tall
// when rendering space out the columns
// # is a wall, . is a pellet, o is a power pellet

char map[29][29] = {
	"############################",// 0
	"#............##............#",// 1
	"#.####.#####.##.#####.####.#",// 2
	"#o####.#####.##.#####.####o#",// 3
	"#.####.#####.##.#####.####.#",// 4
	"#..........................#",// 5
	"#.####.##.########.##.####.#",// 6
	"#.####.##.########.##.####.#",// 7
	"#......##....##....##......#",// 8
	"######.##### ## #####.######",// 9
	"     #.##          ##.#     ",// 10
	"     #.## ###__### ##.#     ",// 11
	"     #.## #      # ##.#     ",// 12
	"######.## #      # ##.######",// 13
	"      .   #      #   .      ",//     14
	"######.## #      # ##.######",// 13
	"     #.## #      # ##.#     ",// 12
	"     #.## ######## ##.#     ",// 11
	"     #.##          ##.#     ",// 10
	"######.##### ## #####.######",// 9
	"#......##....##....##......#",// 8
	"#.####.##.########.##.####.#",// 7
	"#.####.##.########.##.####.#",// 6
	"#..........................#",// 5
	"#.####.#####.##.#####.####.#",// 4
	"#o####.#####.##.#####.####o#",// 3
	"#.####.#####.##.#####.####.#",// 2
	"#............##............#",// 1
	"############################",// 0
};

char** gameRender;

void renderGame() {
	int xPos = 0;
	Vector2* playerPos = (Vector2*)calloc(1, sizeof(Vector2));
	getPlayerPos(&playerPos);
	printf("X = %d Y = %d\n", playerPos->x, playerPos->y);

	for (int y = 0; y < 29; y++) {
		xPos = 0;
		for (char* x = map[y]; *x != '\0'; x++) {
			
			if (playerPos->x == xPos && playerPos->y == y) {
				renderPlayer(getPlayerDirection());
				x++;
				if (*x == '\0') {
					break;
				}
			}

			switch (*x)
			{
			case '#':
				printf(BLUE "%c " RESET_COLOR, *x);
				break;
			case '.':
				printf(WHITE "%c " RESET_COLOR, *x);
				break;
			default:
				printf(WHITE "%c " RESET_COLOR, *x);
				break;
			}
			xPos++;
		}
		printf("\n");
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

char getCell(int x, int y) {
	return *(map[y] + x);
}

void setCell(int x, int y) {
	*(map[y] + x) = ' ';
}