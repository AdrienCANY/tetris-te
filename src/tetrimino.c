#include "tetrimino.h"
#include <stdlib.h>
#include "global.h"
#include "constants.h"
#include "utils.h"

Tetrimino* TTMN_Create(int x, int y, TetriminoType type)
{
    switch(type)
    {
        case TETRIMINO_I: TTMN_CreateI(x, y);  break;
        case TETRIMINO_O: TTMN_CreateO(x, y); break;
        case TETRIMINO_T: TTMN_CreateT(x, y); break;
        case TETRIMINO_L: TTMN_CreateL(x, y); break;
        case TETRIMINO_J: TTMN_CreateJ(x, y);  break;
        case TETRIMINO_Z: TTMN_CreateZ(x, y); break;
        case TETRIMINO_S: TTMN_CreateS(x, y); break;
    }
}

Tetrimino* TTMN_CreateI(int x, int y)
{
    return NULL;
}

Tetrimino* TTMN_CreateO(int x, int y)
{
    return NULL;
}

Tetrimino* TTMN_CreateT(int x, int y)
{
    return NULL;
}

Tetrimino* TTMN_CreateL(int x, int y)
{
    return NULL;
}   

Tetrimino* TTMN_CreateJ(int x, int y)
{
    return NULL;
}

Tetrimino* TTMN_CreateZ(int x, int y)
{
    return NULL;
}

Tetrimino* TTMN_CreateS(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_S;
    ttmn->color = TILE_GREEN;

    ttmn->tiles[0] = (Tile) {1,0};
    ttmn->tiles[1] = (Tile) {2,0};
    ttmn->tiles[2] = (Tile) {0,1};
    ttmn->tiles[3] = (Tile) {1,1};

    return ttmn;
}

void TTMN_Rotate(Tetrimino* ttmn)
{
    // doesnt work for O and I
    if(ttmn->type == TETRIMINO_I )
    {

    }
    else if (ttmn->type != TETRIMINO_O)
    {
        for(int i = 0 ; i < TETRIMINO_TILES_COUNT ; ++i)
        {
            // shift of referential
            ttmn->tiles[i].x--;
            ttmn->tiles[i].y--;

            // rotation of referential
            int temp = ttmn->tiles[i].x;
            ttmn->tiles[i].x = - ttmn->tiles[i].y;
            ttmn->tiles[i].y = temp;

            // undo referential shift
            ttmn->tiles[i].x++;
            ttmn->tiles[i].y++;
        }
    }
}

void TTMN_Render(Tetrimino *ttmn)
{
    setRenderDrawColor(ttmn->color);
    for(int i = 0 ; i < TETRIMINO_TILES_COUNT ; ++i)
    {
        drawTile(ttmn->tiles[i].x + ttmn->x, ttmn->y + ttmn->tiles[i].y);
    }
}

void TTMN_Destroy(Tetrimino *ttmn)
{
    free(ttmn);
    ttmn = NULL;
}

void TTMN_HandleEvent(Tetrimino *ttmn, SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP: ttmn->y--; break;
            case SDLK_DOWN: ttmn->y++; break;
            case SDLK_LEFT: ttmn->x--; break;
            case SDLK_RIGHT: ttmn->x++; break;
            case SDLK_a: TTMN_Rotate(ttmn); break;
        }
    }
}