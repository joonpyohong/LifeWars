

#include "board.h"

#define ITERATIONS      5000
#define ROUNDS          50

typedef struct gameScore
{
    unsigned int roundScore[2][ROUNDS];
    unsigned int totalScore[2];
} gameScore;

void initializeBoard(char *fileName_1, char *fileName_2, gameBoard *board);

void updateBoard(gameBoard *board);

void updateCell(gameBoard *board, int x, int y);

void getNumNeighbors(char *boardState, int x, int y, int *total, int *player_1, int *player_2);

void initializeScore(gameScore *score);

void calculateRoundScore(gameScore *score, gameBoard *board, int round);

void printRoundResult(gameScore *score, int roundNum);

void printGameResult(gameScore *score);

int determineWinner(int score_P1, int score_P2);


