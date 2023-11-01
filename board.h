#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE     "\033[34m"

struct tile{
    int value;
    int row;
    int column;
    struct tile* up;
    struct tile* down;
    struct tile* left;
    struct tile* right;
    int occupyingPlayer;
};


//allocates memory and assigns values to a new tile
struct tile* createTile(int row, int column);


//creates a 2D array of tiles pointing to each other
struct tile** createBoard(int rows, int cols);

//prints the gameboard
void printBoard();

//returns random value from 0 to 3 (not equal probabilities), used when generating new tiles
int randomTileValue();

//calculates and returns sum of values of neighboring tiles
int calculateNeighbours(struct tile* t);

//frees the memory
void freeBoard(struct tile** board, int rows);


#endif
