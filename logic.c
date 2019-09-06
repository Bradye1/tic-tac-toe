#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TOP_LEFT 0
#define TOP_CENTER 1
#define TOP_RIGHT 2
#define MIDDLE_LEFT 3
#define MIDDLE_CENTER 4
#define MIDDLE_RIGHT 5
#define BOTTOM_LEFT 6
#define BOTTOM_CENTER 7
#define BOTTOM_RIGHT 8

const int BOARD_SIZE = 9;
const int SETS_TO_CHECK = 8;

static int TOP_ROW[] = {TOP_LEFT, TOP_CENTER, TOP_RIGHT};
static int MIDDLE_ROW[] = {MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT};
static int BOTTOM_ROW[] = {BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT};
static int LEFT_COLUMN[] = {TOP_LEFT, MIDDLE_LEFT, BOTTOM_LEFT};
static int MIDDLE_COLUMN[] = {TOP_CENTER, MIDDLE_CENTER, BOTTOM_CENTER};
static int RIGHT_COLUMN[] = {TOP_RIGHT, MIDDLE_RIGHT, BOTTOM_RIGHT};
static int DIAGONAL_DOWN[] = {TOP_LEFT, MIDDLE_CENTER, BOTTOM_RIGHT};
static int DIAGONAL_UP[] = {BOTTOM_LEFT, MIDDLE_CENTER, TOP_RIGHT};

//static int SETS_OF_THREE[][3] = {TOP_ROW, MIDDLE_ROW, BOTTOM_ROW, LEFT_COLUMN, MIDDLE_COLUMN, RIGHT_COLUMN, DIAGONAL_DOWN, DIAGONAL_UP};

static int SETS_OF_THREE[8][3] = {TOP_LEFT, TOP_CENTER, TOP_RIGHT, 
				  MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT, 
				  BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT,
				  TOP_LEFT, MIDDLE_LEFT, BOTTOM_LEFT,
				  TOP_CENTER, MIDDLE_CENTER, BOTTOM_CENTER,
				  TOP_RIGHT, MIDDLE_RIGHT, BOTTOM_RIGHT,
				  TOP_LEFT, MIDDLE_CENTER, BOTTOM_RIGHT,
				   BOTTOM_LEFT, MIDDLE_CENTER, TOP_RIGHT};

bool isValidMove(char * gameState, int move) {
	if (move > 8 || move < 0)
		return false;

	return (gameState[move] == ' ');
}

// returns true iff a set of three spaces are all occupied
// by the same char. Prints game over message if true.
bool isComplete(char * gameState, char player, int space1, int space2, int space3) {
	return (gameState[space1] == gameState[space2] && gameState[space2] == gameState[space3] && gameState[space3] != ' ');
}

// check if the set of three has two occupied by the player
// and the third spot is empty
int canComplete(char * gameState, char player, int space1, int space2, int space3) {
	
	//printf("Checking if %c can win with spaces %d, %d, and %d...", player, space1 + 1, space2 + 1, space3 + 1);
	int playerCounter = 0;
	int availableCounter = 0;
	int availableMove = -1;

	if (gameState[space1] == player)
		playerCounter++;
	if (gameState[space2] == player)
		playerCounter++;
	if (gameState[space3] == player)
		playerCounter++;

	if (gameState[space1] == ' ') {
		availableCounter++;
		availableMove = space1;
	}
	if (gameState[space2] == ' ') {
		availableCounter++;
		availableMove = space2;
	}
	if (gameState[space3] == ' ') {
		availableCounter++;
		availableMove = space3;
	}
	if (playerCounter == 2 && availableCounter == 1) {
		//printf("yes!\n");
		//printf("returning %d\n", availableMove);
		return availableMove;
	}

	//printf("Nope!\n");
	return -1;
}

char getWinner(char * gameState, int move) {
	return gameState[move];
}

// see if either player has won or if all spots are taken
bool checkGameOver(char * gameState) {
	int i;
	for (i = 0; i < SETS_TO_CHECK; i++) {
		if (isComplete(gameState, 'X', SETS_OF_THREE[i][0], SETS_OF_THREE[i][1], SETS_OF_THREE[i][2]) || isComplete(gameState, 'O', SETS_OF_THREE[i][0], SETS_OF_THREE[i][1], SETS_OF_THREE[i][2])) {
			printf("Game Over! The winner is %c!\n", getWinner(gameState, SETS_OF_THREE[i][0]));
			return true;
		}
	}

	// check for tie
	for (i = 0; i < BOARD_SIZE; i++) {
		if (isValidMove(gameState, i)) {
			return false;
		}
	}
	// no moves left
	printf("No spaces left. It's a tie!\n");
	return true;	
}

char * doOpponentMove(char * gameState, int move, char opponentChar) {
	//printf("move: %d\n", move);
	//printf("char: %c\n", opponentChar);
	gameState[move] = opponentChar; //segfault
	return gameState;
}


// returns the space that the player can take that
// will result in a win. If no such space exists, returns -1
int aboutToWin(char * gameState, char player) {
	int i;
	for (i = 0; i < SETS_TO_CHECK; i++) {
		int winMove = canComplete(gameState, player, SETS_OF_THREE[i][0], SETS_OF_THREE[i][1], SETS_OF_THREE[i][2]);
		if (winMove != -1) {
			//printf("%c is about to win!\n", player);
			return winMove;
		}
	}

	return -1;
}

char * getNextMove(char * gameState, char opponentChar) {
	
	char myChar;
	if (opponentChar == 'X') {
		myChar = 'O';
	}
	else {
		myChar = 'X';
	}

	// check if I can win
	int myWin = aboutToWin(gameState, myChar);
	if (myWin >= 0) {
		gameState[myWin] = myChar;
		return gameState;
	}

	int opponentWin = aboutToWin(gameState, opponentChar);
	// check if opponent can win
	if (opponentWin >= 0) {
		gameState[opponentWin] = myChar;
		return gameState;
	}	

	// first move?
	bool firstMove = true;
	int i;
	for (i = 0; i < BOARD_SIZE; i++) {
		if (!isValidMove(gameState, i)) {
			firstMove = false;
		}
	}

	// take corner if first move
	if (firstMove) {
		gameState[BOTTOM_RIGHT] = myChar;
		return gameState;
	}

	// check if center is taken
	if (isValidMove(gameState, MIDDLE_CENTER)) {
		gameState[MIDDLE_CENTER] = myChar;
		return gameState;
	}
	
	// if I have the center, take a side
	if (gameState[MIDDLE_CENTER] == myChar) {
		if (isValidMove(gameState, TOP_CENTER)) {
			gameState[TOP_CENTER] = myChar;
			return gameState;
		}
		if (isValidMove(gameState, MIDDLE_LEFT)) {
			gameState[MIDDLE_LEFT] = myChar;
			return gameState;
		}
		if (isValidMove(gameState, MIDDLE_RIGHT)) {
			gameState[MIDDLE_RIGHT] = myChar;
			return gameState;
		}
		if (isValidMove(gameState, BOTTOM_CENTER)) {
			gameState[BOTTOM_CENTER] = myChar;
			return gameState;
		}
	}

	// take a corner
	if (isValidMove(gameState, TOP_LEFT)) {
		gameState[TOP_LEFT] = myChar;
		return gameState;
	}
	if (isValidMove(gameState, TOP_RIGHT)) {
		gameState[TOP_RIGHT] = myChar;
		return gameState;
	}
	if (isValidMove(gameState, BOTTOM_LEFT)) {
		gameState[BOTTOM_LEFT] = myChar;
		return gameState;
	}
	if (isValidMove(gameState, BOTTOM_RIGHT)) {
		gameState[BOTTOM_RIGHT] = myChar;
		return gameState;
	}

	// shouldn't get this far but if it does,
	// then take the first open spot
	for (i = 0; i < BOARD_SIZE; i++) {
		if (isValidMove(gameState, i)) {
			gameState[i] = myChar;
			return gameState;
		}
	}

	// REALLY shouldn't get here
	printf("ERROR! CAN'T FIND VALID MOVE\n");
	return gameState;
}
