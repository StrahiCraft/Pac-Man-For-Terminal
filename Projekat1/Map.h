#ifndef MAP_H_
#define MAP_H_
#include "Vectors.h"

void loadMap(char* mapName);
char getCell(int x, int y);
void setCell(int x, int y);
int getWidth();
int getHeight();
int getPelletCount();
void collectPellet();
#endif // !MAP_H_
