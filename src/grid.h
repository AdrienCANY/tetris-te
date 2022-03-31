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

    int updated;
} Grid;

Grid* Grid_Create(int rows, int columns);
TileColor *Grid_GetTile(int x, int y);
void Grid_Destroy(Grid *grid);
SDL_Texture *Grid_GetTexture(Grid* grid, int x, int y, int tile_size, int show_grid);

SDL_Rect Grid_GetTileRect(int x, int y, int tile_size, int show_grid);




#endif