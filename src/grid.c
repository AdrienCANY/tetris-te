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


TileColor *Grid_GetTile(int x, int y)
{

}

void Grid_Destroy(Grid *grid)
{
    free(grid->tiles);

    free(grid);
    grid = NULL;
}

SDL_Texture *Grid_GetTexture(Grid* grid, int x, int y, int tile_size, int show_grid)
{
    // Create Blank Texture
    int w = grid->columns * tile_size + (show_grid?1:0);
    int h = grid->rows * tile_size + (show_grid?1:0);
    SDL_Texture *texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);

    // Set texture as render target
    SDL_SetRenderTarget(gRenderer, texture);
    
    // draw outline

    SDL_Rect outline = {0,0, w, h};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(gRenderer, &outline);

    // if asked, draw grid

    if( show_grid )
    {
        SDL_SetRenderDrawColor(gRenderer, 0x30, 0x30, 0x30, 0xFF);
        for(int i = tile_size ; i < w ; i += tile_size)
        {
            SDL_RenderDrawLine(gRenderer, i, 0, i, h - 1);
        }
        for(int j = tile_size ; j < h ; j += tile_size)
        {
            SDL_RenderDrawLine(gRenderer, 0, j, w - 1, j);
        }
    }


    // draw tiles
    // TODO


    // unset render target
    SDL_SetRenderTarget(gRenderer, NULL);

    // return texture
    return texture;
}