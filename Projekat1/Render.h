#ifndef RENDERER_H_
#define RENDERER_H_
#include "Vectors.h"
#include "Player.h"

void renderGame();
void renderPlayer(Direction direction);
void renderGhost(Vector2 position, int ghostId);
char getCell(int x, int y);
void setCell(int x, int y);

#endif 
