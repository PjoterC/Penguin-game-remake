#include "gamemechanics.h"



void setPlayerSettings(int* playerSettings, int numPlayers){
    printf("Set player settings: 1 = Human player  2 = AI\n");
    for(int i = 0; i < numPlayers; i++){
        printf("Choose setting for player %d: ", i+1);
        playerSettings[i] = getIntegerInput(1, 2);
    }

}






void placementPhase(int* playerSettings, struct tile** board, struct penguin** pengArr, int numPlayers, int numPenguins, int rows, int cols){ //Do przerobienia pod ai
    int k = 1, x, y;

    printf("Hint: Left top corner has coordinates x = 1 increasing to the right, y = 1 increasing downwards\n");
for (int i = 0; i < numPenguins; i++){
        for(int j = 0; j < numPlayers; j++){

                if(playerSettings[j] == 2) AIPlace(board, pengArr, j+1, numPenguins, numPlayers, rows, cols);
                else{
                switch(j+1){
                case 1: printf("%s", RED); break;
                case 2: printf("%s", GREEN); break;
                case 3: printf("%s", YELLOW); break;
                case 4: printf("%s", BLUE); break;
                }

                printf("Player %d will now choose starting point for his penguin number %d\n", j+1, i+1);
                while(k != 0){
                    printf("Enter x: ");
                    x = getIntegerInput(1, cols);
                    printf("Enter y: ");
                    y = getIntegerInput(1, rows);
                    k = place(pengArr[j+(numPlayers*i)], board, y-1, x-1, rows, cols);
                }
                printf("%s", RESET);
                printBoard(board, rows, cols);
                printf("\n\n");
                k = 1;
                }
        }
}
}


int checkTurnSkip(struct penguin** pengArr, int numPlayers, int numPenguins, int currPlayer){
    int check = 0;
    for(int i = 0; i < numPenguins*numPlayers; i++){
        if(pengArr[i]->playerNum == currPlayer) check += checkMovement(pengArr[i]);
    }
    if(check == numPenguins) return 1;
    else return 0;
}


void playerMove(struct penguin** pengArr, int currPlayer, int numPenguins, int numPlayers){

    int direction = 0;
    int chosenPengNum = 1;
    int dircheck = 1;
    struct penguin* chosenPeng;
    switch(currPlayer){
        case 1: printf("%s", RED); break;
        case 2: printf("%s", GREEN); break;
        case 3: printf("%s", YELLOW); break;
        case 4: printf("%s", BLUE); break;

        }

    printf("Turn of player %d\n", currPlayer); //kolorki
    if(checkTurnSkip(pengArr, numPlayers, numPenguins, currPlayer) != 0){
        printf("Player %d cannot move, skipping turn\n", currPlayer);
        printf("%s", RESET);
        return;
    }
    chosenPeng = findPenguin(pengArr, numPenguins, numPlayers, chosenPengNum, currPlayer);
    if(numPenguins > 1){
        printf("Choose the penguin to move\n");

        printf("Available penguins: ");         //kolorki
        for(int i = 0; i < numPenguins; i++){
            printf("%d ", i+1);
        }
        printf("\n");


        chosenPengNum = getIntegerInput(1, numPenguins);
        chosenPeng = findPenguin(pengArr, numPenguins, numPlayers, chosenPengNum, currPlayer);
        while(checkMovement(chosenPeng) != 0){
            printf("This penguin cannot move, choose another one!\n");
            chosenPengNum = getIntegerInput(1, numPenguins);
            chosenPeng = findPenguin(pengArr, numPenguins, numPlayers, chosenPengNum, currPlayer);
        }

    }

printf("Choose direction of movement: 1 - up  2 - down  3 - left  4 - right\n");
    while(dircheck == 1){
        direction = getIntegerInput(1, 4);
        if(makeMove(chosenPeng, direction) != 0) printf("Cannot move in this direction, choose another one!\n");
        else dircheck = 0;
    }

    printf("%s", RESET);
}


int endGameCheck(struct penguin** pengArr, int numPlayers, int numPenguins){
    int counter = 0;
    for(int i = 0; i < numPenguins*numPlayers; i++){
        counter+=checkMovement(pengArr[i]);
    }
    if(counter == (numPenguins*numPlayers)) return 0;
    else return 1;

}




int calculateDirectionPotential(struct tile* chosenTile){

    int potential = 0;

    if(chosenTile == NULL || chosenTile->value == 0 || chosenTile->occupyingPlayer != 0) potential = 0;
    else{
        potential += chosenTile->value;

        potential += calculateNeighbours(chosenTile);

        potential += (calculateNeighbours(chosenTile->up));
        if(calculateNeighbours(chosenTile->up) != 0) potential -= chosenTile->value;

        potential += (calculateNeighbours(chosenTile->down));
        if(calculateNeighbours(chosenTile->down) != 0) potential -= chosenTile->value;

        potential += (calculateNeighbours(chosenTile->left));
        if(calculateNeighbours(chosenTile->left) != 0) potential -= chosenTile->value;

        potential += (calculateNeighbours(chosenTile->right));
        if(calculateNeighbours(chosenTile->right) != 0) potential -= chosenTile->value;
    }
    //printf("%d\n", potential);
    return potential;
}

int calculateTotalPotential(struct tile* chosenTile){
    int potential = 0;
    if(chosenTile == NULL || chosenTile->value == 0) return 0;
    potential += calculateDirectionPotential(chosenTile->up);
    potential += calculateDirectionPotential(chosenTile->down);
    potential += calculateDirectionPotential(chosenTile->left);
    potential += calculateDirectionPotential(chosenTile->right);
    //printf("\n %d \n", potential);
    return potential;
}






void AIMove(struct penguin** pengArr, int currPlayer, int numPenguins, int numPlayers){
    int potential[] = {0, 0, 0, 0};

    int highestIndex = 0;
    int highestVal = 0;
    int chosenPengNum = 1;
    struct penguin* chosenPeng;
    chosenPeng = findPenguin(pengArr, numPenguins, numPlayers, chosenPengNum, currPlayer);

    if(numPenguins > 1){
        for(int i = 0; i < numPenguins*numPlayers; i++){
            if(pengArr[i]->playerNum == currPlayer && (calculateTotalPotential(chosenPeng->currTile) < calculateTotalPotential(pengArr[i]->currTile))){
                    //printf("Pengchange\n");
                    chosenPeng = pengArr[i];
            }
        }
    }
    switch(currPlayer){
        case 1: printf("%s", RED); break;
        case 2: printf("%s", GREEN); break;
        case 3: printf("%s", YELLOW); break;
        case 4: printf("%s", BLUE); break;
                    }

    printf("Turn of player %d\n", currPlayer); //kolorki



    if(checkTurnSkip(pengArr, numPlayers, numPenguins, currPlayer) != 0){
        printf("Player %d cannot move, skipping turn\n", currPlayer);
        printf("%s", RESET);
        return;
    }



    potential[0] = calculateDirectionPotential(chosenPeng->currTile->up);
    potential[1] = calculateDirectionPotential(chosenPeng->currTile->down);
    potential[2] = calculateDirectionPotential(chosenPeng->currTile->left);
    potential[3] = calculateDirectionPotential(chosenPeng->currTile->right);

    //printf("Potentials: %d %d %d %d\n", potential[0], potential[1], potential[2], potential[3]);

    for(int i = 0; i < 4; i++){
        if(potential[i] > highestVal){
            highestVal = potential[i];
            highestIndex = i;
        }
    }
    if(makeMove(chosenPeng, highestIndex+1) == 1) printf("MOVEMENTERROR");
    printf("Moved to (%d,%d)\n", chosenPeng->currTile->column+1, chosenPeng->currTile->row+1);

    printf("%s", RESET);


}


void AIPlace(struct tile** board, struct penguin** pengArr, int currPlayer, int numPenguins, int numPlayers, int rows, int columns){
    int minimumPotential = 150;
    //printf("AIPLACE\n");
    struct penguin* chosenPeng;
    for(int i = 0; i < numPlayers*numPenguins; i++){
        if(pengArr[i]->playerNum == currPlayer && pengArr[i]->currTile == NULL){
            chosenPeng = pengArr[i];
            break;
        }

    }


    while(minimumPotential > 0){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){

                if(calculateTotalPotential(&board[i][j]) > minimumPotential && board[i][j].value == 1 && board[i][j].occupyingPlayer == 0){
                    //printf("%d %d", i, j);
                    place(chosenPeng, board, i, j, rows, columns);
                    printBoard(board, rows, columns);
                    switch(currPlayer){
                    case 1: printf("%s", RED); break;
                    case 2: printf("%s", GREEN); break;
                    case 3: printf("%s", YELLOW); break;
                    case 4: printf("%s", BLUE); break;
                    }
                    printf("Player %d placed at: %d %d%s\n", currPlayer, chosenPeng->currTile->column+1, chosenPeng->currTile->row+1, RESET);
                    return;
                }
            }
        }
        //printf("Minpot: %d\n", minimumPotential);
        minimumPotential--;

    }






}

