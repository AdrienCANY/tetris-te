#include "tetrimino.h"
#include <stdlib.h>
#include "constants.h"

Tetrimino* TTMN_Create(int x, int y, TetriminoType type)
{
    switch(type)
    {
        case TETRIMINO_I:  break;
        case TETRIMINO_O: break;
        case TETRIMINO_T: break;
        case TETRIMINO_L: break;
        case TETRIMINO_J: break;
        case TETRIMINO_Z: break;
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

    ttmn->tiles[0] = (Tile) {0,1};
    ttmn->tiles[1] = (Tile) {0,2};
    ttmn->tiles[2] = (Tile) {1,0};
    ttmn->tiles[3] = (Tile) {1,1};

    return ttmn;
}

void TTMN_Rotate(Tetrimino* ttmn)
{
    // doesnt work for O and I
    if(ttmn->color )
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

void TTMN_Destroy(Tetrimino *ttmn)
{
    free(ttmn);
    ttmn = NULL;
}