#include "player.h"

Player* Player_Create()
{
    Player *player = malloc(sizeof(Player));

    player->ttmn = NULL;

    player->controls[CONTROL_SOFT_DROP] = SDL_SCANCODE_S;
    player->controls[CONTROL_HARD_DROP] = SDL_SCANCODE_SPACE;
    player->controls[CONTROL_LEFT] = SDL_SCANCODE_A;
    player->controls[CONTROL_RIGHT] = SDL_SCANCODE_D;
    player->controls[CONTROL_ROTATE_CLOCKWISE] = SDL_SCANCODE_E;
    player->controls[CONTROL_ROTATE_COUNTER_CLOCKWISE] = SDL_SCANCODE_Q;
    player->controls[CONTROL_HOLD] = SDL_SCANCODE_W;
    player->controls[CONTROL_TOGGLE_GRID] = SDL_SCANCODE_G;

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