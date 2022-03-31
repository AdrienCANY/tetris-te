#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "game_logic.h"

typedef struct 
{
    // logic

    GameLogic *gamelogic;

    // rendering

    int showGrid;
    int tile_size;
    SDL_Texture* gridTexture;
} Game;

Game* Game_Create();
void Game_HandleEvent(Game* game, SDL_Event *e);
void Game_Render(Game *game);
void Game_Destroy(Game *game);

void Game_UpdateGridTexture(Game *game);
#endif