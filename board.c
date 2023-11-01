#include "board.h"


int randomTileValue(){

    int temp = rand() % 100;
    if(temp < 15) return 0;
    if(temp < 55) return 1;
    if(temp < 85) return 2;
    return 3;
}



struct tile* createTile(int row, int column){
    struct tile* newTile = (struct tile*)malloc(sizeof(struct tile));
    newTile->value = randomTileValue();
    newTile->row = row;
    newTile->column = column;
    newTile->up = NULL;
    newTile->down = NULL;
    newTile->left = NULL;
    newTile->right = NULL;
    newTile->occupyingPlayer = 0;
    return newTile;
}

struct tile** createBoard(int rows, int columns){
    struct tile** board = (struct tile**)malloc(rows * sizeof(struct tile*));
    for (int i = 0; i < rows; i++) {
        board[i] = (struct tile*)malloc(columns * sizeof(struct tile));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = *createTile(i, j);
            if (i > 0) board[i][j].up = &board[i-1][j];
            if (i < rows-1) board[i][j].down = &board[i+1][j];
            if (j > 0) board[i][j].left = &board[i][j-1];
            if (j < columns-1) board[i][j].right = &board[i][j+1];
        }
    }
    return board;
}


void printBoard(struct tile** board, int rows, int columns){

    for(int dashes = 0; dashes < columns; dashes++){
        printf("|---");
        }
        printf("|\n");

    for (int i = 0; i < rows; i++) {
        printf("|");
        for (int j = 0; j < columns; j++) {
            if(board[i][j].occupyingPlayer != 0){
                switch(board[i][j].occupyingPlayer){
                case 1:
                    printf("%s %d %s|", RED, board[i][j].value, RESET);
                    break;
                case 2:
                    printf("%s %d %s|", GREEN, board[i][j].value, RESET);
                    break;
                case 3:
                    printf("%s %d %s|", YELLOW, board[i][j].value, RESET);
                    break;
                case 4:
                    printf("%s %d %s|", BLUE, board[i][j].value, RESET);
                    break;

               }

            }
            else printf(" %d |", board[i][j].value);

        }
        printf("\n");
        for(int dashes = 0; dashes < columns; dashes++){
        printf("|---");
        }
        printf("|\n");

    }
}

int calculateNeighbours(struct tile* t){
    int val = 0;
    if(t == NULL || t->occupyingPlayer != 0 || t->value == 0) return 0;
    else{
        if(t->up != NULL && t->up->occupyingPlayer == 0) val = val + t->up->value;
        if(t->down != NULL && t->down->occupyingPlayer == 0) val = val + t->down->value;
        if(t->left != NULL && t->left->occupyingPlayer == 0) val = val + t->left->value;
        if(t->right != NULL && t->right->occupyingPlayer == 0) val = val + t->right->value;

    //printf("%d\n", val);
       return val;
    }
}



void freeBoard(struct tile** board, int rows) {
    for (int i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
}
