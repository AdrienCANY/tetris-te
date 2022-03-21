#include "game.h"
#include "global.h"

Game* Game_Create()
{
    Game *game = malloc(sizeof(Game));

    game->grid = Grid_Create(100, 100);

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
    Grid_HandleEvent(game->grid, e);
}

void Game_Render(Game *game)
{
    Grid_Render(game->grid);
}

void Game_Destroy(Game *game)
{
    free(game);
    game = NULL;
}
