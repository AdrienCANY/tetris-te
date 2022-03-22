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
    TileColor *tiles;

    Player *player;
    Tetrimino *hold;
} Grid;

Grid* Grid_Create(int x, int y);
void Grid_Render(Grid *grid);
void Grid_HandleEvent(Grid *grid, SDL_Event *e);
void Grid_Destroy(Grid *grid);

void Grid_DrawTetrimno(Grid *grid, Tetrimino *ttmn);
void Grid_DrawTile(Grid *grid, int x, int y, TileColor color);

#endif