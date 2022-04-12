#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "game_logic.h"
#include "texture.h"
#include "constants.h"
#include "animation.h"
#include <SDL_mixer.h>
#include "seed.h"

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

    // prompt
    Texture* promptTexture;

    // line count
    Texture* line_count_texture;

    // speed
    Texture* speed_texture;

    // game length

    Texture *gamelen_Texture;

    // seed

    Texture *seed_texture;

    // animations
    Animation *animation;

    // audio

    Mix_Chunk *hold_sound;
    Mix_Chunk *ttmn_placed_sound;
    Mix_Chunk *game_over_sound;
    Mix_Chunk *line_completed_sound;
    Mix_Chunk *hold_fail_sound;
    
} Game;

Game* Game_Create(int seed);
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