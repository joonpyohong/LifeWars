

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEADER      "#Life 1.06\n"
#define WIDTH       150
#define HEIGHT      90
#define PLAYER_1    '+'
#define PLAYER_2    '@'
#define NO_LIFE     ' '
#define PLAYER_SYMBOL(ID)   ID == 0 ? PLAYER_1 : PLAYER_2
#define PLAYER_ID(SYMBOL)   SYMBOL == PLAYER_1 ? 0 : 1

typedef struct gameBoard {
    char *prevState;
    char *currentState;
} gameBoard;

void openFile(char *fileName, FILE **file);

void createBoard(gameBoard *board);

void destroyBoard(gameBoard *board);

void resetCurrentState(gameBoard *board);

int loadStateFromFile(gameBoard *board, FILE *file, int x0, int y0, char player);

void printBoard(gameBoard *board);

int wrapCoordinate(int val, int max);

void randCoordinates(int *x, int *y);


