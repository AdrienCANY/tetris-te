#ifndef GRID_H_
#define GRID_H_

#include "tile_color.h"
#include <SDL.h>


typedef struct 
{
    // logic properties
    int rows;
    int columns;
    TileColor *tiles;
} Grid;

Grid* Grid_Create(int rows, int columns);
TileColor Grid_GetTileColor(Grid *grid, int x, int y);
void Grid_SetTileColor(Grid *grid, int x, int y, TileColor color);
void Grid_Destroy(Grid *grid);




#endif