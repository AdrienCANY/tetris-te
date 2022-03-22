#ifndef GRID_H_
#define GRID_H_

#include "tile_color.h"
#include "tetrimino.h"
#include <SDL.h>
#include "player.h"


typedef struct 
{
    int h;
    int w;
    int x;
    int y;
    TileColor *blocks;

    Player *player;
    Tetrimino *hold;
} Grid;

Grid* Grid_Create(int x, int y);
void Grid_Render(Grid *grid);
void Grid_HandleEvent(Grid *grid, SDL_Event *e);
void Grid_Destroy(Grid *grid);
TileColor Grid_GetColor(Grid *grid, int x, int y);
void Grid_DrawTile(int x, int y, TileColor color);

#endif