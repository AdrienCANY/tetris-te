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

Tetrimino* TTMN_CreateRand(int x, int y)
{
    TetriminoType type = (TetriminoType) rand() % TETRIMINO_TYPE_COUNT;
    return TTMN_Create(x, y, type);
}

Tetrimino* TTMN_CreateI(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_I;
    ttmn->color = TILE_CYAN;

    ttmn->tiles[0] = (Tile) {0,0};
    ttmn->tiles[1] = (Tile) {1,0};
    ttmn->tiles[2] = (Tile) {2,0};
    ttmn->tiles[3] = (Tile) {3,0};

    ttmn->tiles_count = 4;

    return ttmn;
}

Tetrimino* TTMN_CreateO(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_O;
    ttmn->color = TILE_YELLOW;

    ttmn->tiles[0] = (Tile) {0,0};
    ttmn->tiles[1] = (Tile) {1,0};
    ttmn->tiles[2] = (Tile) {0,1};
    ttmn->tiles[3] = (Tile) {1,1};

    ttmn->tiles_count = 4;

    return ttmn;
}

Tetrimino* TTMN_CreateT(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_T;
    ttmn->color = TILE_PURPLE;

    ttmn->tiles[0] = (Tile) {1,0};
    ttmn->tiles[1] = (Tile) {0,1};
    ttmn->tiles[2] = (Tile) {1,1};
    ttmn->tiles[3] = (Tile) {2,1};

    ttmn->tiles_count = 4;

    return ttmn;
}

Tetrimino* TTMN_CreateL(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_L;
    ttmn->color = TILE_ORANGE;

    ttmn->tiles[0] = (Tile) {0,1};
    ttmn->tiles[1] = (Tile) {1,1};
    ttmn->tiles[2] = (Tile) {2,1};
    ttmn->tiles[3] = (Tile) {2,0};

    ttmn->tiles_count = 4;

    return ttmn;
}   

Tetrimino* TTMN_CreateJ(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_J;
    ttmn->color = TILE_BLUE;

    ttmn->tiles[0] = (Tile) {0,0};
    ttmn->tiles[1] = (Tile) {0,1};
    ttmn->tiles[2] = (Tile) {1,1};
    ttmn->tiles[3] = (Tile) {2,1};

    ttmn->tiles_count = 4;

    return ttmn;
}

Tetrimino* TTMN_CreateZ(int x, int y)
{
    Tetrimino *ttmn = malloc(sizeof(Tetrimino));

    ttmn->x = x;
    ttmn->y = y;
    ttmn->type = TETRIMINO_Z;
    ttmn->color = TILE_RED;

    ttmn->tiles[0] = (Tile) {0,0};
    ttmn->tiles[1] = (Tile) {1,0};
    ttmn->tiles[2] = (Tile) {1,1};
    ttmn->tiles[3] = (Tile) {2,1};

    ttmn->tiles_count = 4;

    return ttmn;
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

    ttmn->tiles_count = 4;

    return ttmn;
}

void TTMN_Rotate(Tetrimino* ttmn)
{
    // O doesn't change when rotating
    if(ttmn->type == TETRIMINO_O)
        return;

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {

        // shift of referential

        if(ttmn->type == TETRIMINO_I)
        {
            if(ttmn->tiles[i].x >= 2) ttmn->tiles[i].x -= 1;
            else ttmn->tiles[i].x -= 2;

            if(ttmn->tiles[i].y >= 2) ttmn->tiles[i].y -= 0;
            else ttmn->tiles[i].y -= 1;
        }
        else 
        {
            ttmn->tiles[i].x--;
            ttmn->tiles[i].y--;
        }
        
        // rotation of referential

        int temp = ttmn->tiles[i].x;
        ttmn->tiles[i].x = - ttmn->tiles[i].y;
        ttmn->tiles[i].y = temp;

        // undo referential shift

        if(ttmn->type == TETRIMINO_I)
        {
            if(ttmn->tiles[i].x >= 0) ttmn->tiles[i].x += 1;
            else ttmn->tiles[i].x += 2;

            if(ttmn->tiles[i].y >= 0) ttmn->tiles[i].y += 0;
            else ttmn->tiles[i].y += 1;
        }
        else 
        {
            ttmn->tiles[i].x++;
            ttmn->tiles[i].y++;
        }

    }
}

void TTMN_Destroy(Tetrimino *ttmn)
{
    free(ttmn);
    ttmn = NULL;
}

void TTMN_Move(Tetrimino* ttmn, int dX, int dY)
{
    ttmn->x += dX;
    ttmn->y += dY;
}