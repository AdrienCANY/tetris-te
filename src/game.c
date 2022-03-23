#include "game.h"
#include "global.h"
#include "constants.h"
#include <time.h>
#include <stdlib.h>

Game* Game_Create()
{
    Game *game = malloc(sizeof(Game));

    game->gamelogic = GL_Create(20, 10, 3, time(NULL));

    return game;
}

void Game_HandleEvent(Game* game, SDL_Event *e)
{
    if(e->type == SDL_QUIT)
    {
        gNextStateID = STATE_EXIT; 
    }
    else if( e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        gNextStateID = STATE_TITLE;
    }
}

void Game_Render(Game *game)
{
    // render grid
    SDL_Texture *texture = Grid_GetTexture(game->gamelogic->grid, 100, 100, TILE_SIZE, 1);
    SDL_Rect rect = {100, 100, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);

    // render player Tetrimino

    // render Tetrimino queue

    // render held Tetrimino
}

void Game_Destroy(Game *game)
{
    GL_Destroy(game->gamelogic);
    free(game);
    game = NULL;
}
