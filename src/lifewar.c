

#include "gameLogic.h"

int main(int argc, char **argv) {
    gameBoard board;
    gameScore score;
    char *fileName[2] = {NULL};
    int i, j;

    if (argc != 3) {
        fprintf(stderr, "ERROR: Wrong number of arguments passed to main()\n");
        exit(EXIT_FAILURE);
    }

    fileName[0] = argv[1];
    fileName[1] = argv[2];

    initializeScore(&score);
    createBoard(&board);
    srand(time(NULL));

    for (i = 0; i < ROUNDS; i++) {
        initializeBoard(fileName[0], fileName[1], &board);

        for (j = 0; j < ITERATIONS; j++) {
            updateBoard(&board);
        }

        calculateRoundScore(&score, &board, i);
        printRoundResult(&score, i);
    }

    printGameResult(&score);
    destroyBoard(&board);
    
    return 0;
}

