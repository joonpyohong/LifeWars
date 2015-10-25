

#include "game.h"

int main(int argc, char **argv) {
    gameBoard board;
    gameScore score;
    char *fileName[2] = {NULL};
    int i, j;

    if (argc != 3) {
        fprintf(stderr, "ERROR: Wrong number of arguments passed to main()\n");
        exit(1);
    }

    fileName[0] = argv[1];
    fileName[1] = argv[2];

    initializeScore(&score);
    createBoard(&board);
    srand(time(NULL));

    for (i = 0; i < GAMES; i++) {
        initializeBoard(fileName[0], fileName[1], &board);

        for (j = 0; j < GENERATIONS; j++) {
            updateBoard(&board);
        }

        calculateGameScore(&score, &board, i);
        printGameResult(&score, i);
    }

    printFinalResult(&score);
    destroyBoard(&board);
    
    return 0;
}

