#ifndef PLAYER_H_
#define PLAYER_H_

#include "tetrimino.h"
#include <SDL.h>

typedef enum
{
    CONTROL_UP,
    CONTROL_DOWN,
    CONTROL_LEFT,
    CONTROL_RIGHT,
    CONTROL_ROTATE
} Control;


typedef struct Player {
    Tetrimino *ttmn; 
    SDL_Scancode controls[5];
    int player_number;
} Player;


Player* Player_Create(Tetrimino *ttmn);
void Player_Destroy(Player* player);
void Player_HandleEvent(Player *player, SDL_Event *e);

#endif
