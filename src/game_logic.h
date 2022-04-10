#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "grid.h"
#include "player.h"
#include "tetrimino.h"
#include "event.h"
#include "timer.h"

typedef struct 
{
    Grid* grid;
    Player *player;
    Tetrimino *hold;
    Tetrimino **queue;
    Tetrimino *landing_shadow;
    int start_x;
    int start_y;

    Timer *timer;
    int dY;
    float speed;
    int soft_dropping;
    int soft_drop_speed;

    int hold_allowed;
    int queue_size;
    
    int score; 
    int level;
    int lines;
    
    int seed;
    // int grid_updated;

    int game_over;
    Event *event;

} GameLogic;

GameLogic* GL_Create(int grid_rows, int grid_columns, int queue_size, int seed);
void GL_Destroy (GameLogic* gl);

void GL_Update(GameLogic *gl);

void GL_MovePlayer(GameLogic *gl, int dx, int dy);
void GL_RotatePlayer(GameLogic *gl, int clockwise);

int GL_CheckWallCollision(GameLogic *logic, Tetrimino* ttmn);
int GL_CheckTileCollision(GameLogic *logic, Tetrimino* ttmn);

void GL_HoldTTMN(GameLogic *logic);
void GL_PopQueue(GameLogic *logic);

void GL_PlaceTTMN(GameLogic *logic);

void GL_StartSoftDrop(GameLogic *logic);
void GL_StopSoftDrop(GameLogic *logic);

void GL_HardDrop(GameLogic *logic);

Tetrimino* GL_GetLandingShadow(GameLogic* logic);

void GL_UpdateLandingShadow(GameLogic *logic);

int GL_IsStarted(GameLogic*);
void GL_Start(GameLogic*);
int GL_IsPaused(GameLogic*);
void GL_Resume(GameLogic*);
void GL_Pause(GameLogic*);
int GL_IsGameOver(GameLogic*);
void GL_Restart(GameLogic*);
void GL_GameOver(GameLogic*);

void GL_Init(GameLogic*);

Event* GL_GetEvent(GameLogic*);

#endif