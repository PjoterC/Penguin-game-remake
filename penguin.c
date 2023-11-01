#include "penguin.h"

struct penguin* createPenguin(int plNum, int pID){
    struct penguin* newPeng = (struct penguin*)malloc(sizeof(struct penguin));
    newPeng->currTile = NULL;
    newPeng->penguinID = pID;
    newPeng->playerNum = plNum;
    newPeng->score = 1;
    return newPeng;
}

struct penguin* findPenguin(struct penguin** pengArr, int numPenguins, int numPlayers, int penguinNum, int playerNum){

    for(int i = 0; i < numPlayers*numPenguins; i++){
        if(pengArr[i]->penguinID == penguinNum && pengArr[i]->playerNum == playerNum) return pengArr[i];
    }
    return NULL;

}



int place(struct penguin* peng, struct tile** board, int x, int y, int rows, int cols){
    //printf("Beforeplacement\n");
    if(x < 0 || x > rows - 1 || y < 0 || y > cols - 1){

        return 1;
    }
    if(board[x][y].value != 1){
        printf("Starting point can only be set on tiles with point value of 1\n");
        return 1;
    }

    board[x][y].value = peng->penguinID;

    board[x][y].occupyingPlayer = peng->playerNum;

    peng->currTile = &board[x][y];
    //printf("AfterPlacement\n");
    return 0;

}

int checkMovement(struct penguin* peng){

    if((peng->currTile->right == NULL || peng->currTile->right->value == 0 || peng->currTile->right->occupyingPlayer != 0) &&
       (peng->currTile->left == NULL || peng->currTile->left->value == 0 || peng->currTile->left->occupyingPlayer != 0) &&
       (peng->currTile->up == NULL || peng->currTile->up->value == 0 || peng->currTile->up->occupyingPlayer != 0) &&
       (peng->currTile->down == NULL || peng->currTile->down->value == 0 || peng->currTile->down->occupyingPlayer != 0)
       ) return 1;
    else return 0;
}

int makeMove(struct penguin* peng, int direction){
    switch(direction){
    case 1: //up
        if((peng->currTile->up == NULL || peng->currTile->up->value == 0 || peng->currTile->up->occupyingPlayer != 0)) return 1;
        peng->score += peng->currTile->up->value;
        peng->currTile->up->value = peng->penguinID;
        peng->currTile->value = 0;
        peng->currTile->occupyingPlayer = 0;
        peng->currTile = peng->currTile->up;
        peng->currTile->value = peng->penguinID;
        peng->currTile->occupyingPlayer = peng->playerNum;
        break;
    case 2: //down
        if((peng->currTile->down == NULL || peng->currTile->down->value == 0 || peng->currTile->down->occupyingPlayer != 0)) return 1;
        peng->score += peng->currTile->down->value;
        peng->currTile->down->value = peng->penguinID;
        peng->currTile->value = 0;
        peng->currTile->occupyingPlayer = 0;
        peng->currTile = peng->currTile->down;
        peng->currTile->value = peng->penguinID;
        peng->currTile->occupyingPlayer = peng->playerNum;
        break;
    case 3: //left
        if((peng->currTile->left == NULL || peng->currTile->left->value == 0 || peng->currTile->left->occupyingPlayer != 0)) return 1;
        peng->score += peng->currTile->left->value;
        peng->currTile->left->value = peng->penguinID;
        peng->currTile->value = 0;
        peng->currTile->occupyingPlayer = 0;
        peng->currTile = peng->currTile->left;
        peng->currTile->value = peng->penguinID;
        peng->currTile->occupyingPlayer = peng->playerNum;
        break;
    case 4: //right
        if((peng->currTile->right == NULL || peng->currTile->right->value == 0 || peng->currTile->right->occupyingPlayer != 0)) return 1;
        peng->score += peng->currTile->right->value;
        peng->currTile->right->value = peng->penguinID;
        peng->currTile->value = 0;
        peng->currTile->occupyingPlayer = 0;
        peng->currTile = peng->currTile->right;
        peng->currTile->value = peng->penguinID;
        peng->currTile->occupyingPlayer = peng->playerNum;
        break;
    }
        return 0;


    }


struct penguin** createPenguinArray(int numPenguins, int numPlayers){
    struct penguin** array = (struct penguin**)malloc(numPenguins * numPlayers * sizeof(struct penguin*));
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i < numPenguins; i++){
        for(int j = 0; j < numPlayers; j++){
            array[j+(numPlayers*i)] = createPenguin(j+1, i+1);


        if (array[j+(numPlayers*i)] == NULL) {

            for (int k = 0; k < i*j; k++) {
                free(array[k]);
            }
            free(array);
            return NULL;
        }
    }
    }
    return array;
}

