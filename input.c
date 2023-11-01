#include "input.h"

int getIntegerInput(int rangestart, int rangeend){
    if(rangestart >= rangeend) return 0;
    int num = 0;

    char buff[100];
    fgets(buff, 100, stdin);
    num = atoi(buff);
    while(num == 0 || num < rangestart || num > rangeend){
        printf("Please enter a number between %d and %d: ", rangestart, rangeend);
        fgets(buff, 100, stdin);
        num = atoi(buff);
    }

    return num;


}
