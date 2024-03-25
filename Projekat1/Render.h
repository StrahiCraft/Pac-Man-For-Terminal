#ifndef RENDERER_H_
#define RENDERER_H_
#include "Vectors.h"

void renderGame();
void renderPlayer(int direction);
void renderGhost(Vector2 position, int ghostId);

#endif 
