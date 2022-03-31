#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "grid.h"
#include "player.h"
#include "tetrimino.h"

typedef struct 
{
    Player *player;
    Grid* grid;
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
void GL_MovePlayer(GameLogic *gl, int dx, int dy);
int GL_CheckWallCollision(GameLogic *logic);
void GL_RotatePlayer(GameLogic *gl, int clockwise);
void GL_Update(GameLogic *gl);
void GL_Destroy (GameLogic* gl);

#endif