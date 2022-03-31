#include "grid.h"
#include <stdlib.h> 
#include "global.h"
#include <SDL.h>

Grid* Grid_Create(int rows, int columns)
{
    Grid *grid = malloc(sizeof(Grid));

    grid->rows = rows;
    grid->columns = columns;
    grid->tiles = calloc(rows * columns, sizeof(TileColor));
    return grid;
}


TileColor Grid_GetTileColor(Grid *grid, int x, int y)
{
    return grid->tiles[(grid->rows*y) + x];
}

void Grid_SetTileColor(Grid *grid, int x, int y, TileColor color)
{
    grid->tiles[(grid->rows*y) + x] = color;
}

void Grid_Destroy(Grid *grid)
{
    free(grid->tiles);

    free(grid);
    grid = NULL;
}
