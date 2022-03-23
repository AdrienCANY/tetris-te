#ifndef TETRIMINO_H_
#define TETRIMINO_H_

#include "tile_color.h"
#include <SDL.h>

typedef enum
{
    TETRIMINO_I,
    TETRIMINO_O,
    TETRIMINO_T,
    TETRIMINO_L,
    TETRIMINO_J,
    TETRIMINO_Z,
    TETRIMINO_S
} TetriminoType;

#define TETRIMINO_TYPE_COUNT 7

typedef struct 
{
    int x, y;
} Tile;

typedef struct 
{
    int x, y;
    Tile tiles[4];
    int tiles_count;
    TileColor color;
    TetriminoType type;
} Tetrimino;

Tetrimino* TTMN_Create(int x, int y, TetriminoType type);
Tetrimino* TTMN_CreateRand(int x, int y);

Tetrimino* TTMN_CreateI(int x, int y);
Tetrimino* TTMN_CreateO(int x, int y);
Tetrimino* TTMN_CreateT(int x, int y);
Tetrimino* TTMN_CreateL(int x, int y);
Tetrimino* TTMN_CreateJ(int x, int y);
Tetrimino* TTMN_CreateZ(int x, int y);
Tetrimino* TTMN_CreateS(int x, int y);

void TTMN_Rotate(Tetrimino* ttmn);
void TTMN_Move(Tetrimino* ttmn, int dX, int dY);

void TTMN_Destroy(Tetrimino *ttmn);

#endif