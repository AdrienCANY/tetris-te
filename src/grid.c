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
    grid->w = GRID_WIDTH * TILE_SIZE + 1;
    grid->h = GRID_HEIGHT * TILE_SIZE + 1;
    grid->blocks = malloc( sizeof(TileColor) * GRID_WIDTH * GRID_HEIGHT );
    grid->ttmn = TTMN_Create(0, 0, TETRIMINO_S);

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

    int ttmn_x = grid->ttmn->x;
    int ttmn_y = grid->ttmn->y;
    for(int i = 0 ; i < TETRIMINO_TILES_COUNT ; ++i)
    {
        int tile_x = grid->ttmn->tiles[i].x;
        int tile_y = grid->ttmn->tiles[i].y;
        Grid_DrawTile(ttmn_x + tile_x, ttmn_y + tile_y, grid->ttmn->color);
    }

    // unset renderer viewport

    SDL_RenderSetViewport(gRenderer, NULL);

    // draw grid outline in white
    
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &outline);

}

void Grid_DrawTile(int x, int y, TileColor color)
{
    switch(color)
    {
        case TILE_BLACK: 
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
            break;
        case TILE_CYAN:
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
            break;
        case TILE_YELLOW:
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
            break;
        case TILE_PURPLE:
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
            break;
        case TILE_ORANGE:
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x7F, 0x00, 0xFF);
            break;
        case TILE_BLUE:
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
            break;
        case TILE_RED:
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
            break;
        case TILE_GREEN:
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
            break;
    }

    SDL_Rect rect = { x * TILE_SIZE + 1, y * TILE_SIZE + 1, TILE_SIZE - 1, TILE_SIZE - 1 };

    SDL_RenderFillRect(gRenderer, &rect);
}

void Grid_Destroy(Grid *grid)
{
    free(grid->blocks);
    TTMN_Destroy(grid->ttmn);
    free(grid);
    grid = NULL;
}

void Grid_HandleEvent(Grid *grid, SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP: grid->ttmn->y--; break;
            case SDLK_DOWN: grid->ttmn->y++; break;
            case SDLK_LEFT: grid->ttmn->x--; break;
            case SDLK_RIGHT: grid->ttmn->x++; break;
            case SDLK_a: TTMN_Rotate(grid->ttmn); break;
        }
    }
}