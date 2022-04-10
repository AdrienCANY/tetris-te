#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "game_logic.h"
#include "texture.h"
#include "constants.h"
#include "animation.h"

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

    // queue
    SDL_Rect queueFrame;
    SDL_Rect queueRects[GAME_QUEUE_SIZE];
    Texture* nextTexture;

    // hold
    SDL_Rect holdFrame;
    SDL_Rect holdRect;
    Texture* holdTexture;

    // animations
    Animation *animation;
    
    Texture* promptTexture;
} Game;

Game* Game_Create();
void Game_HandleEvent(Game* game, SDL_Event *e);
void Game_Render(Game *game);
void Game_Destroy(Game *game);

void Game_Logic(Game *game);


void Game_RenderTTMN(Game *game, Tetrimino* ttmn, SDL_Rect dest );
void Game_RenderTTMN_Grid(Game *game, Tetrimino* ttmn, int x, int y);

void Game_UpdateGridTexture(Game *game);
SDL_Rect Game_GetTileRenderRect(Game *game, int x, int y);
void Game_UpdatePromptText(Game *game, char* text);

void Game_Pause(Game *game);

#endif