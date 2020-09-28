#include "getLine.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------

const char EMPTY             =      ' ';
const int  DRAW              =      777;
const int  NEVERMIND         =       -1;
const int  PLAYER_1          =        1;
const int  PLAYER_2          =        2;
const int  DONE              =      328;
const int  LETTERS_COLOUR    =    white;
const int  BACKGROUND_COLOUR =    bcyan;
const int  COURSOR_COLOUR    =    black;
const int  TO_WIN            =        5;
const int  HARD              =     1337;
const int  LITE              =     2020; 
const int  NONE              =      228;

//----------------------------------------------------------------------------------------------------------

int game                                                                                  ();
int drawField                                    (char *array, int Side, int RedX, int RedY);
int stringXO                               (char *mass, int length, int stringNum, int RedX);
int horizon                                                           (int length, int RedX); 
int moveCoursor (char *array, int N, char arrow, int *X, int *Y, int playerNum, int *Winner);
int isFull                                                              (char *array, int N);
int checkWinner                                  (char *mass, int N, int CoursX, int CoursY);
int check                                     (char *mass, int N, int *winnerLite, int Mode);
int checkHorizon                 (char *mass, int N, int lineNum, int *winnerLite, int Mode);
int checkVertical                (char *mass, int N, int vertNum, int *winnerLite, int Mode);
int checkDiagonalLeft            (char *mass, int N, int diagNum, int *winnerLite, int Mode);
int checkDiagonalRight           (char *mass, int N, int diagNum, int *winnerLite, int Mode);
 
//----------------------------------------------------------------------------------------------------------

int main () {
	game ();
}
 
//----------------------------------------------------------------------------------------------------------

int game () {

	char player1 [20]  =  {};
	char player2 [20]  =  {};
	char string  [10]  =  {};
	char arrow         = '0';
	int  x             =  0 ;
	int  y             =  0 ;
	int  WhoWon        =  0 ; 
	int  N             =  0 ;
	int  monkeyCounter =  0 ;

	printfcolouropen ("\n>>> Wanna PLAY??? A YOU READY????\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
	printfcolouropen (  ">>> How BIG the game will be? Type N to play N*N: ", LETTERS_COLOUR, BACKGROUND_COLOUR);
	
	do {
		if (monkeyCounter != 0)
		printfcolouropen ("\n>>> Are you kidding me? Insert a NUMBER: ", LETTERS_COLOUR, BACKGROUND_COLOUR);

		fgets (string, sizeof (string), stdin);
		++monkeyCounter;
	} while (sscanf (string, "%d", &N) != 1);
		
	char *data = (char*) calloc (N * N, sizeof (data [0]));

	x = (N / 2) + 1;
	y = (N / 2) + 1;
	
	for (int i = 0; i < N * N; ++i)
		data [i] = EMPTY;

	printfcolouropen ("\n>>> HOW DOES YOUR MOM CALL YOU?\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);

	fgets (player1, sizeof (player1), stdin);
	sscanf (player1, "%s", &player1 [0]);
	
	printfcolouropen ("\n>>> WHAT ABOUT YOUR FRIEND?\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);

	fgets (player2, sizeof (player2), stdin);
	sscanf (player2, "%s", &player2 [0]);
	
	printfcolouropen ("\n>>> ALL RIGHT THEN. LET'S STAAAAAAAART....\n", LETTERS_COLOUR, BACKGROUND_COLOUR);

	for (;;) {
		
		do {
		drawField (data, N, x, y);

		printfcolouropen ("\n\n>>> ", LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolour (player1, LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen ("'s turn (X): ", LETTERS_COLOUR, BACKGROUND_COLOUR);

		fgets (string, sizeof (string), stdin);
		sscanf (string, "%c", &arrow);
		} while (moveCoursor (data, N, arrow, &x, &y, PLAYER_1, &WhoWon) != DONE); 

		if (WhoWon != NONE) {
		drawField (data, N, x, y);
			break;
		}

		do {
		drawField (data, N, x, y);

		printfcolouropen ("\n\n>>> ", LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolour (player2, LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen ("'s turn (O): ", LETTERS_COLOUR, BACKGROUND_COLOUR);

		fgets (string, sizeof (string), stdin);
		sscanf (string, "%c", &arrow);
		} while (moveCoursor (data, N, arrow, &x, &y, PLAYER_2, &WhoWon) != DONE); 

		if (WhoWon != NONE) {
 			drawField (data, N, x, y);
			break;
		}
	}
	
	if      (WhoWon == PLAYER_1) {
		printfcolouropen ("\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolour (player1, LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen (" IS A WINNEEEEEEEEEEER!!! (don't worry, ", LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen (player2, LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen (", you played good too)\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
	}

	else if (WhoWon == PLAYER_2) {
		printfcolouropen ("\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolour (player2, LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen (" IS A WINNEEEEEEEEEEER!!! (don't worry, ", LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen (player1, LETTERS_COLOUR, BACKGROUND_COLOUR);
		printfcolouropen (", you played good too)\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
	}


	else if (WhoWon == DRAW) {
		printfcolouropen ("\n\nWHAT? AGAIN??? OK.... JUST A DRAW......\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
	}
	
	else if (WhoWon == 0) {
		printfcolouropen ("\n\nIF YOU SEE THIS THE GAME IS COMPLETE\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);
	}

	else
		printfcolouropen ("\n\nAAAAAAAHH!!! Something WRONG!!!"
			      "	WHO IS THE WINNER????????? \n\n", COURSOR_COLOUR, bwhite);
	
	free (data);
}
 
//----------------------------------------------------------------------------------------------------------

int drawField (char *array, int Side, int RedX, int RedY) {

	printfcolouropen ("\n\n\n\n\n\n\n", LETTERS_COLOUR, BACKGROUND_COLOUR);

	if (RedY == Side)
		horizon (Side, RedX);
	else 
		horizon (Side, NEVERMIND);
	for (int j = 1; j <= Side; ++j) {
		if      (RedY == Side + 1 - j) {
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
 
//----------------------------------------------------------------------------------------------------------

int horizon (int length, int RedX) {
	if (RedX == 1)
		printfcolouropen ("\n|", COURSOR_COLOUR, BACKGROUND_COLOUR);
	else 
		printfcolouropen ("\n|", LETTERS_COLOUR, BACKGROUND_COLOUR);
	for (int i = 1; i <= length; ++i) {
		if      (RedX == i + 1) {
			printfcolour ("---", LETTERS_COLOUR, BACKGROUND_COLOUR);
			printfcolour ("|", COURSOR_COLOUR, BACKGROUND_COLOUR);
		}
		else if (RedX == i)
			printfcolour ("---|", COURSOR_COLOUR, BACKGROUND_COLOUR);
		else
			printfcolour ("---|", LETTERS_COLOUR, BACKGROUND_COLOUR);
	}
}
 
//----------------------------------------------------------------------------------------------------------

int stringXO (char *mass, int length, int stringNum, int RedX) {
	if (RedX == 1)
		printfcolouropen ("\n|", COURSOR_COLOUR, BACKGROUND_COLOUR);
	else
		printfcolouropen ("\n|", LETTERS_COLOUR, BACKGROUND_COLOUR);

	for (int i = 1; i <= length; ++i) {
		if (RedX == i + 1) {
			printfcolour (" ", LETTERS_COLOUR, BACKGROUND_COLOUR);
			switch (mass [length * (length - stringNum) + i - 1]) {
				case 'X': printfcolour ("X", LETTERS_COLOUR, BACKGROUND_COLOUR);
					  break;
				case 'O': printfcolour ("O", LETTERS_COLOUR, BACKGROUND_COLOUR);
					  break;
				case ' ': printfcolour (" ", LETTERS_COLOUR, BACKGROUND_COLOUR);
					  break;		
			}
			printfcolour (" |", COURSOR_COLOUR, BACKGROUND_COLOUR);
		}
		else if (RedX == i) {
			switch (mass [length * (length - stringNum) + i - 1]) {
				case 'X': printfcolour (" X |", COURSOR_COLOUR, BACKGROUND_COLOUR);
					  break;
				case 'O': printfcolour (" O |", COURSOR_COLOUR, BACKGROUND_COLOUR);
					  break;
				case ' ': printfcolour ("   |", COURSOR_COLOUR, BACKGROUND_COLOUR);
					  break;			
			}	  
		}
		else {
			switch (mass [length * (length - stringNum) + i - 1]) {
				case 'X': printfcolour (" X |", LETTERS_COLOUR, BACKGROUND_COLOUR);
					  break;
				case 'O': printfcolour (" O |", LETTERS_COLOUR, BACKGROUND_COLOUR);
					  break;
				case ' ': printfcolour ("   |", LETTERS_COLOUR, BACKGROUND_COLOUR);
					  break;	
			}
		}
	}
}
 
//----------------------------------------------------------------------------------------------------------

int moveCoursor (char *array, int N, char arrow, int *X, int *Y, int playerNum, int *Winner) {
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
				break;
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
								*Winner = checkWinner (array, N, *X, *Y);
								return DONE;
				}
				break;
		case 'o':
				if (playerNum == 2 && array [ ((*Y) - 1) * N + ((*X) - 1) ] == EMPTY) {
								array [ ((*Y) - 1) * N + ((*X) - 1) ] = 'O';
								*Winner = checkWinner (array, N, *X, *Y);
								return DONE;
				}
				break;
		case 'Q': 
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
				break;
		case 'W':
				if ((*Y) + 1 <= N)
					++(*Y);
				break;
		case 'A':
				if ((*X) - 1 >= 1)
					--(*X);
				break;
		case 'S':
				if ((*Y) - 1 >= 1)
					--(*Y);
				break;
		case 'D':
				if ((*X) + 1 <= N)
					++(*X);
				break;
		case 'X':
				if (playerNum == 1 && array [ ((*Y) - 1) * N + ((*X) - 1) ] == EMPTY) {
								array [ ((*Y) - 1) * N + ((*X) - 1) ] = 'X';
								*Winner = checkWinner (array, N, *X, *Y);
								return DONE;
				}
				break;
		case 'O':
				if (playerNum == 2 && array [ ((*Y) - 1) * N + ((*X) - 1) ] == EMPTY) {
								array [ ((*Y) - 1) * N + ((*X) - 1) ] = 'O';
								*Winner = checkWinner (array, N, *X, *Y);
								return DONE;
				}
				break;
	}
	return !DONE;	
}
 
//----------------------------------------------------------------------------------------------------------
			
int isFull (char *array, int N) {
	int filled = 0;
	for (int i = 0; i < N * N; ++i)
		if (array [i] != EMPTY)
			++filled;
	return filled == N * N;
}

//----------------------------------------------------------------------------------------------------------

int checkWinner (char *mass, int N, int CoursX, int CoursY) {
	int winner = NONE;

	if      (N < TO_WIN)
		check (mass, N, &winner, LITE);
	else if (N >= TO_WIN)
		check (mass, N, &winner, HARD);

	if (isFull (mass, N) && winner == NONE) {
		drawField (mass, N, CoursX, CoursY);
		winner = DRAW;
	}
	return winner;
}

//-----------------------------------------------------------------------------------------------------------

int check (char *mass, int N, int *winnerLite, int Mode) {
	if      (Mode == LITE) {
	for (int i = 1; i <= N; ++i)
		checkHorizon (mass, N, i, winnerLite, LITE);

	for (int j = 1; j <= N; ++j)
		checkVertical (mass, N, j, winnerLite, LITE);
	
	for (int k = 1; k <= 2*N; ++k)
		checkDiagonalLeft (mass, N, k, winnerLite, LITE);

	for (int k = 1; k <= 2*N; ++k)
		checkDiagonalRight (mass, N, k, winnerLite, LITE);
	}

	else if (Mode == HARD) {
	for (int i = 1; i <= N; ++i)
		checkHorizon (mass, N, i, winnerLite, HARD);

	for (int j = 1; j <= N; ++j)
		checkVertical (mass, N, j, winnerLite, HARD);
	
	for (int k = 1; k <= 2*N; ++k)
		checkDiagonalLeft (mass, N, k, winnerLite, HARD);

	for (int k = 1; k <= 2*N; ++k)
		checkDiagonalRight (mass, N, k, winnerLite, HARD);
	}
}

//-----------------------------------------------------------------------------------------------------------

int checkHorizon (char *mass, int N, int lineNum, int *winnerLite, int Mode) {
	int countX = 0, countO = 0;

	for (int i = 0; i < N; ++i) {
		if      (mass [ (lineNum - 1) * N + i ] == 'X')
			++countX;
		else if (mass [ (lineNum - 1) * N + i ] == 'O')
			++countO;
	}
	if      (Mode == LITE) {
		if      (countX == N)
			*winnerLite = PLAYER_1;
		else if (countO == N)
			*winnerLite = PLAYER_2;
	}
	else if (Mode == HARD) {
		if      (countX >= TO_WIN)
			*winnerLite = PLAYER_1;
		else if (countO >= TO_WIN)
			*winnerLite = PLAYER_2;
	}
}

//-----------------------------------------------------------------------------------------------------------

int checkVertical (char *mass, int N, int vertNum, int *winnerLite, int Mode) {
	int countX = 0, countO = 0;

	for (int i = 0; i < N; ++i) {
		if      (mass [ N * i + vertNum - 1 ] == 'X')
			++countX;
		else if (mass [ N * i + vertNum - 1 ] == 'O')
			++countO;
	}
	if      (Mode == LITE) {
		if      (countX == N)
			*winnerLite = PLAYER_1;
		else if (countO == N)
			*winnerLite = PLAYER_2;
	}
	else if (Mode == HARD) {
		if      (countX >= TO_WIN)
			*winnerLite = PLAYER_1;
		else if (countO >= TO_WIN)
			*winnerLite = PLAYER_2;
	}
}

//-----------------------------------------------------------------------------------------------------------

int checkDiagonalLeft (char *mass, int N, int diagNum, int *winnerLite, int Mode) {
	int countX = 0, countO = 0;
	
	if      (diagNum > N)
		for (int i = 0; diagNum - N + i <= N; ++i) {
			if      (mass [ N * (N - 1) + (diagNum - N - 1) - (N - 1) * i ] == 'X')
				++countX;
			else if (mass [ N * (N - 1) + (diagNum - N - 1) - (N - 1) * i ] == 'O')
				++countO;
		}

	else if (diagNum <= N)
		for (int i = 0; diagNum > i; ++i) {
			if      (mass [ (diagNum - 1) + (N - 1) * i ] == 'X')
				++countX;
			else if (mass [ (diagNum - 1) + (N - 1) * i ] == 'O')
				++countO;
		}
	if      (Mode == LITE) {
		if      (countX == N)
			*winnerLite = PLAYER_1;
		else if (countO == N)
			*winnerLite = PLAYER_2;
	}
	else if (Mode == HARD) {
		if      (countX >= TO_WIN)
			*winnerLite = PLAYER_1;
		else if (countO >= TO_WIN)
			*winnerLite = PLAYER_2;
	}
}

//-----------------------------------------------------------------------------------------------------------

int checkDiagonalRight (char *mass, int N, int diagNum, int *winnerLite, int Mode) {
	int countX = 0, countO = 0;
	
	if      (diagNum > N)
		for (int i = 0; diagNum - N < i; ++i) {
			if      (mass [ N * (N - 1) + (diagNum - N - 1) - (N + 1) * i ] == 'X')
				++countX;
			else if (mass [ N * (N - 1) + (diagNum - N - 1) - (N + 1) * i ] == 'O')
				++countO;
		}

	else if (diagNum <= N)
		for (int i = 0; diagNum + i <= N; ++i) {
			if      (mass [ (diagNum - 1) + (N + 1) * i ] == 'X')
				++countX;
			else if (mass [ (diagNum - 1) + (N + 1) * i ] == 'O')
				++countO;
		}
	
	if      (Mode == LITE) {
		if      (countX == N)
			*winnerLite = PLAYER_1;
		else if (countO == N)
			*winnerLite = PLAYER_2;
	}
	else if (Mode == HARD) {
		if      (countX >= TO_WIN)
			*winnerLite = PLAYER_1;
		else if (countO >= TO_WIN)
			*winnerLite = PLAYER_2;
	}
}

	
