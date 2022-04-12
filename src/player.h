#ifndef PLAYER_H_
#define PLAYER_H_

#include "tetrimino.h"
#include <SDL.h>

typedef enum
{
    CONTROL_LEFT,
    CONTROL_RIGHT,
    CONTROL_ROTATE_CLOCKWISE,
    CONTROL_ROTATE_COUNTER_CLOCKWISE,
    CONTROL_HOLD,
    CONTROL_SOFT_DROP,
    CONTROL_HARD_DROP,
    CONTROL_TOGGLE_GRID,
    CONTROL_COUNT // only meant to get the count of controls
} Control;


typedef struct Player {
    Tetrimino *ttmn;
    SDL_Scancode controls[CONTROL_COUNT];
} Player;


Player* Player_Create();
void Player_Destroy(Player* player);
void Player_HandleEvent(Player *player, SDL_Event *e);

void Player_Load(Player *player, Tetrimino *ttmn);

#endif
