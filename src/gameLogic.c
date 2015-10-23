

#include "gameLogic.h"

void initializeBoard(char *fileName_1, char *fileName_2, gameBoard *board) {
    FILE *files[2];
    int origin[2][2];
    int foundConflict = 0, i;

    openFile(fileName_1, &files[0]);
    openFile(fileName_2, &files[1]);

    do {
        resetCurrentState(board);

        for (i = 0; i < 2; i ++) {
            randCoordinates(&origin[i][0], &origin[i][1]);
            foundConflict = loadStateFromFile(board, files[i], origin[i][0], origin[i][1], PLAYER_SYMBOL(i));
        }
    } while (foundConflict);

    fclose(files[0]);
    fclose(files[1]);
}

void updateBoard(gameBoard *board) {
    int i, j;

    memcpy(board->prevState, board->currentState, WIDTH * HEIGHT * sizeof(char));

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            updateCell(board, j, i);
        }
    }
}

void updateCell(gameBoard *board, int x, int y) {
    int n, n_P1, n_P2;
    int idx = y * WIDTH + x;

    getNumNeighbors(board->prevState, x, y, &n, &n_P1, &n_P2);
    
    /* survival */
    if ((n == 2 || n == 3) && board->prevState[idx] != NO_LIFE) {
        board->currentState[idx] = board->prevState[idx];
        return;
    }

    /* birth */
    if (n == 3 && board->prevState[idx] == NO_LIFE) {
        if (n_P1 > n_P2) {
            board->currentState[idx] = PLAYER_1;
        } else {
            board->currentState[idx] = PLAYER_2;
        }

        return;
    }

    /* death */
    board->currentState[idx] = NO_LIFE;
}

void getNumNeighbors(char *boardState, int x, int y, int *total, int *player_1, int *player_2) {
    int i, j;
    int newX, newY;
    int cnt = 0, n[2] = {0};
    char symbol;

    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
                newX = wrapCoordinate(x + i, WIDTH);
                newY = wrapCoordinate(y + j, HEIGHT);

                if ((symbol = boardState[newY * WIDTH + newX]) != NO_LIFE) {
                    cnt++;
                    n[PLAYER_ID(symbol)]++;
                }
            }
        }
    }

    *total = cnt;
    *player_1 = n[0];
    *player_2 = n[1];
}

void initializeScore(gameScore *score) {
    int i;

    for (i = 0; i < ROUNDS; i++) {
        score->roundScore[0][i] = 0;
        score->roundScore[1][i] = 0;
    }

    score->totalScore[0] = 0;
    score->totalScore[1] = 0;
}

void calculateRoundScore(gameScore *score, gameBoard *board, int roundNum) {
    int i, j;
    char symbol;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            symbol = board->currentState[i * WIDTH + j];

            if (symbol != NO_LIFE) {
                score->roundScore[PLAYER_ID(symbol)][roundNum]++;
            }
        }
    }

    score->totalScore[0] += score->roundScore[0][roundNum];
    score->totalScore[1] += score->roundScore[1][roundNum];
}

void printRoundResult(gameScore *score, int roundNum) {
    int winner;

    winner = determineWinner(score->roundScore[0][roundNum], score->roundScore[1][roundNum]);

    if (winner == -1) {
        printf("%8d%8d%8d    Draw\n", roundNum, score->roundScore[0][roundNum], score->roundScore[1][roundNum]);
    } else {
        printf("%8d%8d%8d    Player %d\n", roundNum, score->roundScore[0][roundNum], score->roundScore[1][roundNum], winner + 1);
    }
}

void printGameResult(gameScore *score) {
    int winner;

    winner = determineWinner(score->totalScore[0], score->totalScore[1]);

    if (winner == -1) {
        printf("Game ended in a draw\n");
    } else {
        printf("Player %d wins by %d cells to %d cells\n", winner + 1, score->totalScore[winner], score->totalScore[!winner]);
    }
}

int determineWinner(int score_P1, int score_P2) {
    int winner;

    if (score_P1 > score_P2) {
        winner = 0;
    }

    if (score_P1 < score_P2) {
        winner = 1;
    }

    if (score_P1 == score_P2) {
        winner = -1;
    }

    return winner;
}


