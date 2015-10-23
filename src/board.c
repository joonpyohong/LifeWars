

#include "board.h"

void openFile(char *fileName, FILE **file) {
    if ((*file = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "ERROR: cannot open file %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void createBoard(gameBoard *board) {
    board->currentState = (char *)malloc(WIDTH * HEIGHT * sizeof(char));
    board->prevState = (char *)malloc(WIDTH * HEIGHT * sizeof(char));

    if (board->currentState == NULL || board->prevState == NULL) {
        fprintf(stderr, "ERROR: memory allocation error\n");
        exit(EXIT_FAILURE);
    }
}

void destroyBoard(gameBoard *board) {
    free(board->currentState);
    free(board->prevState);
}

void resetCurrentState(gameBoard *board) {
    int i;

    for (i = 0; i < WIDTH * HEIGHT; i++) {
        board->currentState[i] = NO_LIFE;
    }
}

int loadStateFromFile(gameBoard *board, FILE *file, int x0, int y0, char player) {
    char line[64] = {'\0'};
    int x, y, newX, newY, idx;

    fgets(line, 64, file);

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

void printBoard(gameBoard *board) {
    int i;

    for (i = 0; i < WIDTH * HEIGHT; i++) {
        printf("%c ", board->currentState[i]);

        if ((i + 1) % WIDTH == 0) {
            printf("\n");
        }
    }

    printf("\n");
}

int wrapCoordinate(int val, int max) {
    if (val < 0) {
        return (max + val) % max;
    }

    return val % max;
}

void randCoordinates(int *x, int *y) {
    *x = rand() % WIDTH;
    *y = rand() % HEIGHT;
}


