#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H
#include "penguin.h"
#include "board.h"
#include<stdio.h>
#include "input.h"
#include<assert.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE     "\033[34m"


//takes console input and sets settings to differentiate between human and ai turn
void setPlayerSettings(int* playerSettings, int numPlayers);

//handles placement phase
void placementPhase(int* playerSettings, struct tile** board, struct penguin** pengArr, int numPlayers, int numPenguins, int rows, int cols);


//checks if player should skip a turn - all of player's penguins can't make a move
int checkTurnSkip(struct penguin** pengArr, int numPlayers, int numPenguins, int currPlayer);

//makes player choose a penguin to move (if more than 1) and the direction of movement
void playerMove(struct penguin** pengArr, int currPlayer, int numPenguins, int numPlayers);


//checks whether no player can make a move and game should end
int endGameCheck(struct penguin** pengArr, int numPlayers, int numPenguins);


//Chooses penguin based on potential points gain and moves it in the optimal direction
void AIMove(struct penguin** pengArr, int currPlayer, int numPenguins, int numPlayers);

//Places a penguin during placement phase based on point potential of a tile
void AIPlace(struct tile** board, struct penguin** pengArr, int currPlayer, int numPenguins, int numPlayers, int rows, int columns);


//calculates the point potential for a specific tile (used during movement for AIMove choice of movement direction)
int calculateDirectionPotential(struct tile* chosenTile);

//calculates total potential for a specific tile (used during movement and placement for AI, checks potential in all 4 directions from the chosenTile)
int calculateTotalPotential(struct tile* chosenTile);




#endif // GAMEMECHANICS_H
