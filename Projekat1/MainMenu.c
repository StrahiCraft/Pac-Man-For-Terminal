#include "MainMenu.h"
#include "Render.h"

#include <stdio.h>
#include <string.h>

char* logo[] = {
	" __              ",YELLOW"____"    RESET_COLOR,"            ",            BLUE"_______   ______   __            _____                       \n"        RESET_COLOR,
	"|  |    /\\      ",YELLOW"/"       RESET_COLOR, "  0 ", YELLOW"/"RESET_COLOR,BLUE"              |     |        |  |  |\\    /|   |    |\\   |    /\\    | \n"RESET_COLOR,
	"|__|   /__\\    ", YELLOW"|    /"  RESET_COLOR,"    ______",              BLUE"     |     |_____   |__|  | \\  / |   |    | \\  |   /__\\   | \n"         RESET_COLOR,
	"|     /    \\   ", YELLOW"|    \\" RESET_COLOR,"   |______|",             BLUE"    |     |        |\\    |  \\/  |   |    |  \\ |  /    \\  | \n"           RESET_COLOR,
	"|    /      \\   ",YELLOW"\\____\\"BLUE,"              |     |______  | \\   |      | __|__  |   \\| /      \\ |____\n"RESET_COLOR
};

int selectedOption = 0;

void renderLogo() {
	for (int i = 0; i < 20; i++) {
		printf("%s", logo[i]);
	}
	printf("\n\n\n");
}

int navigateMenu(char input) {
	if (input == 'w' || input == 'a') {
		selectedOption--;
	}
	if (input == 's' || input == 'd') {
		selectedOption++;
	}

	if (selectedOption > 2) {
		selectedOption = 2;
	}else if (selectedOption < 0) {
		selectedOption = 0;
	}

	if (input == ' ') {
		return selectedOption + 1;
	}
	if (input == 'q') {
		return 3;
	}
	return -1;
}

void renderButtons() {
	if (selectedOption == 0) {
		printf(YELLOW " >START\n\n" RESET_COLOR);
	}
	else
	{
		printf("  START\n\n");
	}
	if (selectedOption == 1) {
		printf(YELLOW " >SCOREBOARD\n\n" RESET_COLOR);
	}
	else
	{
		printf("  SCOREBOARD\n\n");
	}
	if (selectedOption == 2) {
		printf(RED " >QUIT\n\n" RESET_COLOR);
	}
	else
	{
		printf("  QUIT\n\n");
	}
}