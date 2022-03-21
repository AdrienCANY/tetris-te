#include "grid.h"
#include "constants.h"
#include <stdlib.h>
#include <SDL.h>
#include "global.h"


Grid* Grid_Create(int x, int y)
{
    Grid *grid = malloc(sizeof(Grid));
    
    grid->x = x;
    grid->y = y;
    grid->w = GRID_WIDTH * TILE_SIZE;
    grid->h = GRID_HEIGHT * TILE_SIZE;
    grid->blocks = malloc( sizeof(TileColor) * GRID_WIDTH * GRID_HEIGHT );
    grid->ttmn = TTMN_Create(0, 0, TETRIMINO_S);

    grid->test = (Tile) {0,0};

    return grid;
}


void Grid_Render(Grid *grid)
{
    // draw grid's inner lines
    SDL_Rect outline = {grid->x, grid->y, grid->w, grid->h};
    // SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    for(int i = outline.x + TILE_SIZE ; i < outline.w + outline.x ; i += TILE_SIZE)
    {
        SDL_RenderDrawLine(gRenderer, i, outline.y, i, outline.h + outline.y - 1);
    }
    for(int i = outline.y + TILE_SIZE ; i < outline.y + outline.h ; i += TILE_SIZE)
    {
        SDL_RenderDrawLine(gRenderer, outline.x, i, outline.x + outline.w - 1, i);
    }

    // draw grid outline in white
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &outline);

    // draw test tile
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect tile_rect = {
        outline.x + ( grid->test.x * TILE_SIZE ) + 1,
        outline.y + ( grid->test.y * TILE_SIZE ) + 1,
        TILE_SIZE - 2,
        TILE_SIZE - 2
    };
    SDL_RenderFillRect(gRenderer, &tile_rect);

}

void Grid_Destroy(Grid *grid)
{

}

TileColor Grid_GetColor(Grid *grid, int x, int y)
{

}

void Grid_HandleEvent(Grid *grid, SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP: grid->test.y--; break;
            case SDLK_DOWN: grid->test.y++; break;
            case SDLK_LEFT: grid->test.x--; break;
            case SDLK_RIGHT: grid->test.x++; break;
        }
    }
}