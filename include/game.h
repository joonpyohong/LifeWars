

#include "board.h"

#define GAMES           50
#define GENERATIONS     5000

typedef struct gameScore
{
    unsigned int roundScore[2][GAMES];
    unsigned int totalScore[2];
} gameScore;

void initializeBoard(char *fileName_1, char *fileName_2, gameBoard *board);

void updateBoard(gameBoard *board);

void updateCell(gameBoard *board, int x, int y);

void getNumNeighbors(char *boardState, int x, int y, int *total, int *player_1, int *player_2);

void initializeScore(gameScore *score);

void calculateGameScore(gameScore *score, gameBoard *board, int round);

void printGameResult(gameScore *score, int roundNum);

void printFinalResult(gameScore *score);

int determineWinner(int score_P1, int score_P2);


