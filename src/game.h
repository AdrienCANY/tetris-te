#ifndef GAME_H_
#define GAME_H_

#include "constants.h"
#include <SDL.h>

typedef struct 
{
 
} Game;

Game* Game_Create();
void Game_HandleEvent(Game* game, SDL_Event *e);
void Game_Render(Game *game);
void Game_Destroy(Game *game);

#endif