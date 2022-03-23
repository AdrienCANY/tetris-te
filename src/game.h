#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "game_logic.h"

typedef struct 
{
    GameLogic *gamelogic;
} Game;

Game* Game_Create();
void Game_HandleEvent(Game* game, SDL_Event *e);
void Game_Render(Game *game);
void Game_Destroy(Game *game);

#endif