#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user_interface.c"
#include "logic.c"

char * getOpponentOrder() {
	char * choice;
	choice = malloc(6);
	while (1) {
		if (scanf("%s", choice)) {
			if (strcmp(choice, "first") == 0 || strcmp(choice, "second") == 0) {
				return choice;
			}
			else {
				printf("You must enter \"first\" or \"second\".\n");
			}
		}
		else {
			printf("You must enter \"first\" or \"second\". Bye!\n");
			return "Error";
		}
	}
}

char getOpponentChar() {
	char opponent;
	while (1) {
		if (scanf("%c", &opponent)) {
			if (opponent == 'X' || opponent == 'O') {
				return opponent;
			}
			else {
				printf("You must choose X or O.\n");
			}
		}
		else {
			printf("You must choose X or O. Bye!\n");
			return 'E';
		}
	}
}

int main() {
	int turn = 1;
	char gameState[] = "         ";
	char opponent;
	char * opponentOrder;
	bool opponentOdds = false;
	int opponentMove;
	int myMove;

	printf("Would you like to be X or O?\n");
	opponent = getOpponentChar();
	
	if (opponent == 'E')
		return 0;
	
	printf("Would you like to go first or second?\n");
	opponentOrder = getOpponentOrder();

	if (strcmp(opponentOrder, "Error") == 0)
		return 0;

	if (strcmp(opponentOrder, "first") == 0)
		opponentOdds = true;

	printf("You're choice: %c\n", opponent);
	printf("You are going: %s\n", opponentOrder);

	// game start
	drawGame(gameState);
	while (!checkGameOver(gameState)) {
		// check whose turn it is
		// opponent's turn
		if (turn % 2 == 1 && opponentOdds || turn % 2 == 0 && !opponentOdds) {
			opponentMove = inputMove();
			while (!isValidMove(gameState, opponentMove)) {
				opponentMove = inputMove();
			}

			doOpponentMove(gameState, opponentMove, opponent);
			turn++;
		}
		// my turn
		else {
			printf("Taking my turn...\n");
			getNextMove(gameState, opponent);
			turn++;
		}
		drawGame(gameState);
	}

}
