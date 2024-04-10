#ifndef RENDERER_H_
#define RENDERER_H_
#include "Vectors.h"
#include "Player.h"

// colors
#define RESET_COLOR   "\x1b[0m"
#define BLUE		  "\x1b[34m"
#define WHITE		  "\x1b[97m"
#define YELLOW        "\x1b[93m"

// ghost colors
#define RED           "\x1b[91m"
#define CYAN          "\x1b[96m"
#define PINK          "\x1b[95m"
#define ORANGE        "\x1b[33m"

// ghost flash colors
#define GRAY          "\x1b[90m"
#define BRIGHT_BLUE   "\x1b[96m"

void setupMap();
void renderGame();
void renderPlayer(Direction direction);
void renderGhost(int ghostId);

#endif 
