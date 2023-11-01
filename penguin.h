#ifndef PENGUIN_H
#define PENGUIN_H

#include "board.h"

struct penguin{
    int playerNum;
    int penguinID;
    struct tile* currTile;
    int score;
};

//allocates memory and creates a penguin with given playerNum and penguinID
struct penguin* createPenguin(int plNum, int pID);

//returns pointer to penguin with a given penguinID and playerNum if penguin in the array, null otherwise
struct penguin* findPenguin(struct penguin** pengArr, int numPenguins, int numPlayers, int penguinNum, int playerNum);

//places a penguin on a tile with given coordinates
int place(struct penguin* peng, struct tile** board, int x, int y, int rows, int cols);


//checks if penguin can move, returns 0 if yes, 1 if no
int checkMovement(struct penguin* peng);


//moves penguin in a specific direction: 1 - up  2 - down  3 - left  4 - right
int makeMove(struct penguin* peng, int direction);

//allocates memory for the array and creates penguins
struct penguin** createPenguinArray(int numPenguins, int plNum);

#endif


