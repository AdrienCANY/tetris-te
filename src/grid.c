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


TileColor *Grid_GetTileColor(int x, int y)
{
    // TODO
}

void Grid_Destroy(Grid *grid)
{
    free(grid->tiles);

    free(grid);
    grid = NULL;
}
