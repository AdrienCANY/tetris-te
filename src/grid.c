#include "grid.h"
#include "constants.h"
#include <stdlib.h>
#include <SDL.h>
#include "utils.h"
#include "global.h"


Grid* Grid_Create(int x, int y)
{
    Grid *grid = malloc(sizeof(Grid));
    
    grid->x = x;
    grid->y = y;
    grid->w = GRID_WIDTH * TILE_SIZE + 1;
    grid->h = GRID_HEIGHT * TILE_SIZE + 1;

    grid->tiles = malloc( sizeof(TileColor) * GRID_WIDTH * GRID_HEIGHT );
    Tetrimino *ttmn = TTMN_Create(0, 0, TETRIMINO_I);
    grid->player = Player_Create(ttmn);

    return grid;
}


void Grid_Render(Grid *grid)
{
    // Set render view port

    SDL_Rect outline = {grid->x, grid->y, grid->w, grid->h};
    SDL_RenderSetViewport(gRenderer, &outline);

    // draw grid's inner lines

    SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);
    
    for(int i = TILE_SIZE ; i < outline.w ; i += TILE_SIZE)
    {
        SDL_RenderDrawLine(gRenderer, i, 0, i, outline.h - 1);
    }
    for(int i = TILE_SIZE ; i < outline.h ; i += TILE_SIZE)
    {
        SDL_RenderDrawLine(gRenderer, 0, i, outline.w - 1, i);
    }

    // draw tetrimino

    Grid_DrawTetrimno(grid, grid->player->ttmn);

    // unset renderer viewport

    SDL_RenderSetViewport(gRenderer, NULL);

    // draw grid outline in white
    
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &outline);

}



void Grid_Destroy(Grid *grid)
{
    free(grid->tiles);
    Player_Destroy(grid->player);
    free(grid);
    grid = NULL;
}

void Grid_HandleEvent(Grid *grid, SDL_Event *e)
{
    Player_HandleEvent(grid->player, e);
}

void Grid_DrawTetrimno(Grid *grid, Tetrimino *ttmn)
{
    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        Grid_DrawTile(grid, ttmn->x + ttmn->tiles[i].x, ttmn->y + ttmn->tiles[i].y, ttmn->color);
    }
}

void Grid_DrawTile(Grid *grid, int x, int y, TileColor color)
{
    setRenderDrawColor(color);
    drawTile(x, y);
}