#include "utils.h"
#include "stdio.h"
#include "constants.h"
#include <string.h>


int min( int a, int b )
{
    return (a < b) ? a : b;
}


int max( int a, int b )
{
    return ( a > b ) ? a : b;
}

int in(int needle, int* haystack, int size)
{
    for(int i = 0 ; i < size ; ++i)
    {
        if(haystack[i] == needle)
            return 1;
    }
    return 0;
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
        case TILE_GREY:
            SDL_SetRenderDrawColor(gRenderer, 0x30, 0x30, 0x30, 0xFF);
            break;
    }
}


void drawTile(int x, int y)
{
    SDL_Rect rect = { x * TILE_SIZE + 1, y * TILE_SIZE + 1, TILE_SIZE - 1, TILE_SIZE - 1 };

    SDL_RenderFillRect(gRenderer, &rect);
}

void printGrid(Grid *grid)
{
    printf("     ");
    for(int a = 0 ; a < grid->columns ; ++a)
    {
        printf("%d ", a);
    }
    printf("\n------------------------\n");

    for(int a = 0 ; a < grid->rows ; ++a)
    {
        printf("%02d | ", a);
        for(int b = 0 ; b < grid->columns; ++b)
        {
            TileColor color = Grid_GetTileColor(grid, b, a);
            printf("%d ", color);
        }
        printf("\n");
    }
}

char* getAlphaFromInt (int n)
{
    char* result = calloc(5, sizeof(char));


    char* ptr = result;
    while( ptr < result + 4)
    {
        *ptr++ = 'A' + (n % 26);
        n /= 26;
    }
    strrev(result);
    return result;
}

int getIntFromAlpha (char* code)
{
    int result = 0;
    int exp = 1;
    for(int i = strlen(code) - 1 ; i >= 0 ; --i)
    {
        result += (code[i] - 'A') * exp;
        exp *= 26;
    }
    return result;
}