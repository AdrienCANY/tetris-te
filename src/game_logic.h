#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "grid.h"
#include "player.h"
#include "tetrimino.h"

typedef struct 
{
    Grid* grid;
    Player *player;
    Tetrimino *hold;
    Tetrimino **queue;
    int queue_size;
    int score; 
    int level;
    int lines;
    int seed;
    int grid_updated;
} GameLogic;

GameLogic* GL_Create(int grid_rows, int grid_columns, int queue_size, int seed);
void GL_Destroy (GameLogic* gl);

void GL_Update(GameLogic *gl);

void GL_MovePlayer(GameLogic *gl, int dx, int dy);
void GL_RotatePlayer(GameLogic *gl, int clockwise);

int GL_CheckWallCollision(GameLogic *logic);
int GL_CheckTileCollision(GameLogic *logic);

void GL_PlaceTTMN(GameLogic *logic);


#endif