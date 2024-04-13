#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "Scoreboard.h"

#include <stdio.h>

void diplayScoreboard(){
	FILE* scoreboard = fopen("scoreboard.txt", "r");
	char chr;
	while ((chr = fgetc(scoreboard)) != EOF)
	{
		printf("%c", chr);
	}
	fclose(scoreboard);

	printf("\nPress anything to go back to menu...");
	getch();
}

void addScore(int score, char name[3]) {
	FILE* scoreboard = fopen("scoreboard.txt", "a");

	fprintf(scoreboard, "\n%.2fs %c%c%c\n", (float)score / 10, name[0], name[1], name[2]);

	fclose(scoreboard);
}