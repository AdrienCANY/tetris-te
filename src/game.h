#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "game_logic.h"
#include "texture.h"

typedef struct 
{
    // logic

    GameLogic *gamelogic;

    // rendering

    int showGrid;
    int tile_size;
    SDL_Texture* gridTexture;
    int grid_w;
    int grid_h;
    Texture* nextTexture;
    Texture* holdTexture;
} Game;

Game* Game_Create();
void Game_HandleEvent(Game* game, SDL_Event *e);
void Game_Render(Game *game);
void Game_Destroy(Game *game);

void Game_Logic(Game *game);

void Game_UpdateGridTexture(Game *game);
SDL_Rect Game_GetTileRenderRect(Game *game, int x, int y);
#endif