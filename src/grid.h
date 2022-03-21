#ifndef GRID_H_
#define GRID_H_

#include "block.h"

typedef struct 
{
    int height;
    int width;
    int x;
    int y;

    Block* grid;
} Grid;

#endif