#include <stdio.h>
#include <string.h>

const int BOARD_SPACES = 9;

int drawGame(char * gameState) {
	if (strlen(gameState) != 9) {
		return -1;
	}

	int i;
	for (i = 0; i < BOARD_SPACES; i++) {
		if (gameState[i] != 'X' && gameState[i] != 'O' && gameState[i] != ' ') {
			return -1;
		}
	}

	printf("----------------------------------------------------\n");
	printf("Current Board:\n");
	printf("%c|%c|%c\n", gameState[0], gameState[1], gameState[2]);
	printf("-+-+-\n");
	printf("%c|%c|%c\n", gameState[3], gameState[4], gameState[5]);
	printf("-+-+-\n");
	printf("%c|%c|%c\n\n", gameState[6], gameState[7], gameState[8]);
	return 0;
}

int inputMove() {
	// print options
	printf("Options:\n");
	printf("%d|%d|%d\n", 1, 2, 3);
	printf("-+-+-\n");
	printf("%d|%d|%d\n", 4, 5, 6);
	printf("-+-+-\n");
	printf("%d|%d|%d\n\n", 7, 8, 9);
	printf("Please choose the number of the spot you'd like to take next.\n");
	
	int choice;
	
	// get input
	while (1) {
                if (scanf("%d", &choice)) {
                        if (choice > 0 && choice < 10) {
                                return choice - 1;
                        }
                        else {
                                printf("You must choose a number from 1 to 9\n");
                        }
                }
                else {
                        printf("You must choose a number. Bye!\n");
                        return -1;
                }
        }
}
