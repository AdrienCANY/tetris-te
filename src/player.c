#include "player.h"

Player* Player_Create(Tetrimino *ttmn)
{
    Player *player = malloc(sizeof(Player));

    player->ttmn = ttmn;

    player->controls[CONTROL_UP] = SDL_SCANCODE_UP;
    player->controls[CONTROL_DOWN] = SDL_SCANCODE_DOWN;
    player->controls[CONTROL_LEFT] = SDL_SCANCODE_LEFT;
    player->controls[CONTROL_RIGHT] = SDL_SCANCODE_RIGHT;
    player->controls[CONTROL_ROTATE] = SDL_SCANCODE_SPACE; 
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

void Player_HandleEvent(Player *player, SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        if( e->key.keysym.scancode == player->controls[CONTROL_UP])
        {
            TTMN_Move(player->ttmn, 0, -1);
        }
        else if( e->key.keysym.scancode == player->controls[CONTROL_DOWN])
        {
            TTMN_Move(player->ttmn, 0, 1);
        }
        else if( e->key.keysym.scancode == player->controls[CONTROL_LEFT])
        {
            TTMN_Move(player->ttmn, -1, 0);
        }
        else if( e->key.keysym.scancode == player->controls[CONTROL_RIGHT])
        {
            TTMN_Move(player->ttmn, 1, 0);
        }
        else if( e->key.keysym.scancode == player->controls[CONTROL_ROTATE])
        {
            TTMN_Rotate(player->ttmn);
        }
    }
}