

#include "board.h"

void openFile(char *fileName, FILE **file) {
    if ((*file = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "ERROR: cannot open file %s\n", fileName);
        exit(1);
    }
}

void createBoard(gameBoard *board) {
    board->currentState = (char *)malloc(WIDTH * HEIGHT * sizeof(char));
    board->prevState = (char *)malloc(WIDTH * HEIGHT * sizeof(char));

    if (board->currentState == NULL || board->prevState == NULL) {
        fprintf(stderr, "ERROR: memory allocation error\n");
        exit(1);
    }
}

void destroyBoard(gameBoard *board) {
    free(board->currentState);
    free(board->prevState);
}

/*
Loads the starting coordinates for a player onto the board.
Returns 0 on success, 1 if a space is already occupied.
*/
int loadStateFromFile(gameBoard *board, FILE *file, int x0, int y0, char player) {
    char line[16];
    int x, y, newX, newY, idx;

    fgets(line, 16, file);

    while (fscanf(file, "%d %d", &x, &y) != EOF) {
        newX = wrapCoordinate(x0 + x, WIDTH);
        newY = wrapCoordinate(y0 + y, HEIGHT);
        idx = newY * WIDTH + newX;
        
        if (board->currentState[idx] != NO_LIFE) {
            return 1;
        }

        board->currentState[idx] = player;
    }

    return 0;
}

int wrapCoordinate(int val, int max) {
    return val < 0 ? ((max + val) % max) : (val % max);
}

void randCoordinates(int *x, int *y) {
    *x = rand() % WIDTH;
    *y = rand() % HEIGHT;
}


