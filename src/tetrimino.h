#ifndef TETRIMINO_H_
#define TETRIMINO_H_

#include "block.h"

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

typedef struct 
{
    Block blocks[4];
} Tetrimino;

Tetrimino* TTMN_Create(TetriminoType type);

Tetrimino* TTMN_CreateI();
Tetrimino* TTMN_CreateO();
Tetrimino* TTMN_CreateT();
Tetrimino* TTMN_CreateL();
Tetrimino* TTMN_CreateJ();
Tetrimino* TTMN_CreateZ();
Tetrimino* TTMN_CreateS();

void TTMN_Destroy(Tetrimino *ttmn);

#endif