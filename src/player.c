#include "player.h"

Player* Player_Create(Tetrimino *ttmn)
{
    Player *player = malloc(sizeof(Player));

    player->ttmn = ttmn;

    player->controls[CONTROL_UP] = SDL_SCANCODE_UP;
    player->controls[CONTROL_DOWN] = SDL_SCANCODE_DOWN;
    player->controls[CONTROL_LEFT] = SDL_SCANCODE_LEFT;
    player->controls[CONTROL_RIGHT] = SDL_SCANCODE_RIGHT;
    player->controls[CONTROL_ROTATE_CLOCKWISE] = SDL_SCANCODE_E;
    player->controls[CONTROL_ROTATE_COUNTER_CLOCKWISE] = SDL_SCANCODE_Q;

    return player;
}

void Player_Load(Player *player, Tetrimino *ttmn)
{
    if(player->ttmn != NULL)
        TTMN_Destroy(player->ttmn);
        
    player->ttmn = ttmn;
}

void Player_Destroy(Player* player)
{
    if(player->ttmn != NULL)
        TTMN_Destroy(player->ttmn);
    
    free(player);
    player = NULL;
}