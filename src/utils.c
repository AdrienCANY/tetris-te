#include "utils.h"
#include "constants.h"

int min( int a, int b )
{
    return (a < b) ? a : b;
}


int max( int a, int b )
{
    return ( a > b ) ? a : b;
}


void setRenderDrawColor(TileColor color)
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
}


void drawTile(int x, int y)
{
    SDL_Rect rect = { x * TILE_SIZE + 1, y * TILE_SIZE + 1, TILE_SIZE - 1, TILE_SIZE - 1 };

    SDL_RenderFillRect(gRenderer, &rect);
}