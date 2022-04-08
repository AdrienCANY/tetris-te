#include "grid.h"
#include <stdlib.h> 
#include "global.h"
#include <SDL.h>
#include "utils.h"

Grid* Grid_Create(int rows, int columns)
{
    Grid *grid = malloc(sizeof(Grid));

    grid->rows = rows;
    grid->columns = columns;
    grid->tiles = calloc(rows * columns, sizeof(TileColor));
    return grid;
}

void Grid_Clear(Grid* grid)
{
    for( int y = 0 ; y < grid->rows ; y++ )
    {
        for( int x = 0 ; x < grid->columns ; x++ )
        {
            Grid_SetTileColor(grid, x, y, TILE_BLACK);
        }
    }
}


TileColor Grid_GetTileColor(Grid *grid, int x, int y)
{
    int i = ( grid->columns * y ) + x;
    return grid->tiles[(grid->columns*y) + x];
}

void Grid_SetTileColor(Grid *grid, int x, int y, TileColor color)
{
    grid->tiles[(grid->columns*y) + x] = color;
}

void Grid_Destroy(Grid *grid)
{
    free(grid->tiles);

    free(grid);
    grid = NULL;
}
