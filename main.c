#include <stdio.h>
#include <stdlib.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE     "\033[34m"
#include <assert.h>

#include "board.h"
#include "penguin.h"
#include "gamemechanics.h"
int main()
{
    printf("%s", RESET); //turning terminal white (just in case)

    printf("Welcome to the Penguin Game!\n");
    printf("The objective is to move the pawns (Penguins) on the rectangular board of ice floes, in order to collect points (fish).\n");
    printf("The fish floes are displayed on the board as numbers 1, 2, 3 (indicating the amount of fish on the ice floe).\n");
    printf("The penguins are displayed as numbers with different colors, each player has their own color.\n");
    printf("When penguin leaves the ice floe, it will sink, leaving behind a water tile (0).\n");
    printf("Players can move 1 tile in 4 directions.\n");
    printf("Movement that ends on a water tile, other penguin or outside of the board is prohibited.\n");
    printf("The game ends when no player can make a move.\n\n");
    printf("Enter number of players (2-4): ");
    int numPlayers = getIntegerInput(2, 4);
    printf("Enter number of penguins for each player (1-2): ");
    int numPenguins = getIntegerInput(1, 2);



//GAME SETUP
    int playerSettings[] = {0, 0, 0, 0};
    setPlayerSettings(playerSettings, numPlayers);

    //printf("\n%d %d %d %d\n", playerSettings[0], playerSettings[1], playerSettings[2], playerSettings[3]);

    int score[] = {0, 0, 0, 0};



    printf("Enter number of rows for the board: ");
    int rows = getIntegerInput(8, 16);
    printf("Enter number of columns for the board: ");
    int cols = getIntegerInput(8, 16);


    srand(time(NULL));
    struct tile** board = createBoard(rows, cols);
    struct penguin** pengArr = createPenguinArray(numPenguins, numPlayers);
    int currPlayer = 1;

    /*
    for(int i = 0; i < numPenguins*numPlayers; i++){
        printf("%d %d\n", pengArr[i]->penguinID, pengArr[i]->playerNum); //check if penguins are initialized correctly
    }
    */






    printBoard(board, rows, cols);



    placementPhase(playerSettings, board, pengArr, numPlayers, numPenguins, rows, cols);

    //printf("Neighbours: %d", calculateNeighbours(&board[5][6]));






//MOVEMENT PHASE
    int end = 1;
    while(end != 0){
        if(playerSettings[currPlayer-1] == 1){
            playerMove(pengArr, currPlayer, numPenguins, numPlayers);
            printBoard(board, rows, cols);
        }
        else{
            AIMove(pengArr, currPlayer, numPenguins, numPlayers);
            printBoard(board, rows, cols);
        }
        if(currPlayer == numPlayers) currPlayer = 1;
        else currPlayer++;
        end = endGameCheck(pengArr, numPlayers, numPenguins);
    }








//COUNTING SCORES

    for(int i = 0; i < numPenguins*numPlayers; i++){
        score[pengArr[i]->playerNum - 1] += pengArr[i]->score;
    }




    for(int i = 0; i < numPlayers; i++){
        switch(i){
                case 0:
                    printf("%sPlayer %d: %d points%s\n", RED, i+1, score[i], RESET);
                    break;
                case 1:
                    printf("%sPlayer %d: %d points%s\n", GREEN, i+1, score[i], RESET);
                    break;
                case 2:
                    printf("%sPlayer %d: %d points%s\n", YELLOW, i+1, score[i], RESET);
                    break;
                case 3:
                    printf("%sPlayer %d: %d points%s\n", BLUE, i+1, score[i], RESET);
                    break;
        }
    }



    freeBoard(board, rows);
    for (int i = 0; i < numPenguins; i++) {
            free(pengArr[i]);
        }
        free(pengArr);


    return 0;
}
