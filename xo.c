#include "getLine.h"
#include <stdlib.h>

const char EMPTY     = ' ';
const int  DRAW      = 777;
const int  NEVERMIND =  -1;
const int  PLAYER_1  =   1;
const int  PLAYER_2  =   2;
const int  DONE      = 328;

int game ();
int drawField (char *array, int Side, int RedX, int RedY);
int stringXO (char *mass, int length, int stringNum, int RedX);
int horizon (int length, int RedX); 
int moveCursor (char *array, int N, char arrow, int *X, int *Y, int playerNum, int *Winner);
int isFull (char *array, int N);
 
int main () {
		
	game ();
}

int game () {

	char player1 [50] = {};
	char player2 [50] = {};
	char string  [50] = {};
	char arrow   = '0';
	int  x = 0, y = 0;
	int    WhoWon = 0;
	int  i = 0, N = 0;

	printfcolour ("\n>>> Wanna PLAY??? A YOU READY????\n\n", yellow, bblue);
	printfcolour (  ">>> How BIG the game will be? Type N to play N*N: ", yellow, bblue);
	
	do {
		if (i != 0)
		printfcolour ("\n>>> Are you kidding me? Insert a NUMBER: ", yellow, bblue);

		fgets (string, sizeof (string), stdin);
		++i;
	} while (sscanf (string, "%d", &N) != 1);
		
	char *data = (char*) calloc (N * N, sizeof (data [0]));
	x = (N / 2) + 1;
	y = (N / 2) + 1;
	
	for (int i = 0; i < N * N; ++i)
		data [i] = EMPTY;

	printfcolour ("\n", yellow, bblue);
	printfcolour (">>> HOW DOES YOUR MOM CALL YOU?\n\n", yellow, bblue);
	fgets (player1, sizeof (player1), stdin);
	sscanf (player1, "%s", &player1 [0]);
	
	printfcolour ("\n", yellow, bblue);
	printfcolour (">>> WHAT ABOUT YOUR FRIEND?\n\n", yellow, bblue);
	fgets (player2, sizeof (player2), stdin);
	sscanf (player2, "%s", &player2 [0]);
	
	printfcolour ("\n", yellow, bblue);
	printfcolour (">>> ALL RIGHT THEN. LET'S STAAAAAAAART....\n", yellow, bblue);

	for (;;) {
		
		do {
		WhoWon  = drawField (data, N, x, y);

		printfcolour (" \n", yellow, bblue);
		printfcolour (">>> ", yellow, bblue);
		printf ("%s", player1);
		printfcolour ("'s turn (X): ", yellow, bblue);

		fgets (string, sizeof (string), stdin);
		sscanf (string, "%c", &arrow);
		} while (moveCursor (data, N, arrow, &x, &y, PLAYER_1, &WhoWon) != DONE); 

		if (WhoWon)
			break;

		do {
		WhoWon  = drawField (data, N, x, y);

		printfcolour (" \n", yellow, bblue);
		printfcolour (">>> ", yellow, bblue);
		printf ("%s", player2);
		printfcolour ("'s turn (O): ", yellow, bblue);

		fgets (string, sizeof (string), stdin);
		sscanf (string, "%c", &arrow);
		} while (moveCursor (data, N, arrow, &x, &y, PLAYER_2, &WhoWon) != DONE); 

		if (WhoWon) 
			break;
	}
	
	if (WhoWon == 1)
		printf ("\n%s IS A WINNEEEEEEEEEEER!!!"
			"(don't worry, %s, you played good too)\n", player1, player2);

	else if (WhoWon == 2)
		printf ("\n%s IS A WINNEEEEEEEEEEER!!!"
			"(don't worry, %s, you played good too)\n", player2, player1);

	else if (WhoWon == DRAW)
		printfcolour ("\nWHAT? AGAIN??? OK.... JUST A DRAW......\n", yellow, bblue);
	
	else if (WhoWon == 0) {
		printfcolour ("\n", yellow, bblue);
		printfcolour ("IF YOU SEE THIS THE GAME IS COMPLETE\n", yellow, bblue);
	}

	else
		printfcolour ("\nAAAAAAAHH!!! Something WRONG!!!"
			      "	WHO IS THE WINNER????????? \n", red, bwhite);
	
	free (data);
}

int drawField (char *array, int Side, int RedX, int RedY) {
	if (RedY == Side)
		horizon (Side, RedX);
	else 
		horizon (Side, NEVERMIND);
	for (int j = 1; j <= Side; ++j) {
		if (RedY == Side + 1 - j) {
			stringXO (array, Side, j, RedX);
			horizon (Side, RedX);
		}
		else if (RedY == Side - j) {
			stringXO (array, Side, j, NEVERMIND);
			horizon (Side, RedX);
		}
		else {
			stringXO (array, Side, j, NEVERMIND);
			horizon (Side, NEVERMIND);
		}
	}
	return 0;
}       

int horizon (int length, int RedX) {
	if (RedX == 1)
		printfcolour (" \n|", red, bblue);
	else 
		printfcolour (" \n|", yellow, bblue);
	for (int i = 1; i <= length; ++i) {
		if (RedX == i + 1) {
			printfcolour ("---", yellow, bblue);
			printfcolour ("|", red, bblue);
		}
		else if (RedX == i)
			printfcolour ("---|", red, bblue);
		else
			printfcolour ("---|", yellow, bblue);
	}
}

int stringXO (char *mass, int length, int stringNum, int RedX) {
	if (RedX == 1)
		printfcolour ("\n|", red, bblue);
	else
		printfcolour ("\n|", yellow, bblue);

	for (int i = 1; i <= length; ++i) {
		if (RedX == i + 1) {
			printfcolour (" ", yellow, bblue);
			switch (mass [length * (length - stringNum) + i - 1]) {
				case 'X': printfcolour ("X", yellow, bblue);
					  break;
				case 'O': printfcolour ("O", yellow, bblue);
					  break;
				case ' ': printfcolour (" ", yellow, bblue);
					  break;		
			}
			printfcolour (" |", red, bblue);
		}
		else if (RedX == i) {
			switch (mass [length * (length - stringNum) + i - 1]) {
				case 'X': printfcolour (" X |", red, bblue);
					  break;
				case 'O': printfcolour (" O |", red, bblue);
					  break;
				case ' ': printfcolour ("   |", red, bblue);
					  break;			
			}	  
		}
		else {
			switch (mass [length * (length - stringNum) + i - 1]) {
				case 'X': printfcolour (" X |", yellow, bblue);
					  break;
				case 'O': printfcolour (" O |", yellow, bblue);
					  break;
				case ' ': printfcolour ("   |", yellow, bblue);
					  break;	
			}
		}
	}
}

int moveCursor (char *array, int N, char arrow, int *X, int *Y, int playerNum, int *Winner) {
	switch (arrow) {
		case 'q': 
				switch (playerNum) {
						case 1:
								*Winner = 2;
								return DONE;
								break;
						case 2: 
								*Winner = 1;
								return DONE;
								break;
					}
		case 'w':
				if ((*Y) + 1 <= N)
					++(*Y);
				break;
		case 'a':
				if ((*X) - 1 >= 1)
					--(*X);
				break;
		case 's':
				if ((*Y) - 1 >= 1)
					--(*Y);
				break;
		case 'd':
				if ((*X) + 1 <= N)
					++(*X);
				break;
		case 'x':
				if (playerNum == 1 && array [ ((*Y) - 1) * N + ((*X) - 1) ] == EMPTY) {
								array [ ((*Y) - 1) * N + ((*X) - 1) ] = 'X';
								if (isFull (array, N)) {
									*Winner = DRAW;
									drawField (array, N, *X, *Y);
								}
								return DONE;
				}
				break;
		case 'o':
				if (playerNum == 2 && array [ ((*Y) - 1) * N + ((*X) - 1) ] == EMPTY) {
								array [ ((*Y) - 1) * N + ((*X) - 1) ] = 'O';
								if (isFull (array, N)) {
									*Winner = DRAW;
									drawField (array, N, *X, *Y);
								}
								return DONE;
				}
				break;
	}
	return !DONE;	
}
				
int isFull (char *array, int N) {
	int filled = 0;
	for (int i = 0; i < N * N; ++i)
		if (array [i] != EMPTY)
			++filled;
	return filled == N * N;
}
