#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Map.h"
#include "Ghosts.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>

char* map;
int width;
int height;

int pelletCount;

int loadMap(char* name) {
	FILE* mapFile = fopen(name, "r");

	if (mapFile == NULL) {
		return 1;
	}

	width = 0;
	height = 0;

	pelletCount = 0;

	char digit = '0';
	while((digit = fgetc(mapFile)) != '\n')
	{
		width = width * 10 + (digit - '0');
	}
	while ((digit = fgetc(mapFile)) != '\n')
	{
		height = height * 10 + (digit - '0');
	}

	map = calloc(width * height + 1, sizeof(char));
	int ghostId = 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*(map + width * y + x) = fgetc(mapFile);
			if (*(map + width * y + x) == 'G') {
				setupGhost(ghostId, x, y);
				ghostId++;
			}
			if (*(map + width * y + x) == 'P') {
				setupPlayer(x, y);
			}
			if (*(map + width * y + x) == '.') {
				pelletCount++;
			}
		}
	}

	fclose(mapFile);
	return 0;
}

char getCell(int x, int y) {
	if (x < 0 || y < 0 || x > getWidth() || y > getWidth()) {
		return ' ';
	}
	return *(map + width * y + x);
}

void setCell(int x, int y) {
	*(map + width * y + x) = ' ';
}

int getWidth() {
	return width;
}

int getHeight() {
	return height;
}

int getPelletCount() {
	return pelletCount;
}

void collectPellet() {
	--pelletCount;
}