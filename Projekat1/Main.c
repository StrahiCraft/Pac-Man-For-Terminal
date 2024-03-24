#include <stdio.h>
#include "Player.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
	printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");

	int input = 0;

	while (input != 'q' && input != 27)
	{
		input = getch();
		handleInput(input);
	}
	return 0;
}