#include "player.h"

Player* Player_Create(Tetrimino *ttmn)
{
    Player *player = malloc(sizeof(Player));

    player->ttmn = ttmn;

    static int player_count = 0;
    player_count++;
    player->player_number = player_count;

    if(player->player_number == 1)
    {
        
    } 
}

void Player_Load(Player *player, Tetrimino *ttmn)
{
    if(player->ttmn != NULL)
        TTMN_Destroy(player->ttmn);
    player->ttmn = ttmn;
}

void Player_Destroy(Player* player)
{
    playerNb--;
    TTMN_Destroy(player->ttmn);
    free(player);
    player = NULL;
}

void Player_HandleEvent(Player *player, SDL_Event *e)
{

}