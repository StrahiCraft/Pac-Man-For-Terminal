#ifndef RENDERER_H_
#define RENDERER_H_
#include "Vectors.h"
#include "Player.h"

void setupMap();
void renderGame();
void renderPlayer(Direction direction);
void renderGhost(Vector2 position, int ghostId);

#endif 
