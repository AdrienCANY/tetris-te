#include "game.h"
#include "global.h"
#include "constants.h"
#include <time.h>
#include <stdlib.h>

Game* Game_Create()
{
    Game *game = malloc(sizeof(Game));

    game->gamelogic = GL_Create(20, 10, 3, time(NULL));
    game->showGrid = 1;
    game->tile_size = TILE_SIZE;
    Game_UpdateGridTexture(game);

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

    // if the grid has been updated (ie if tiles have been dropped), update the grid texture

    if( game->gamelogic->grid->updated )
    {
        Game_UpdateGridTexture(game);
        game->gamelogic->grid->updated = 0;
    }
}

void Game_Render(Game *game)
{
    // set render viewport for grid elements

    int w = game->gamelogic->grid->columns * TILE_SIZE + game->showGrid;
    int h = game->gamelogic->grid->rows * TILE_SIZE + game->showGrid;
    SDL_Rect viewport = {100, 100, w, h};
    SDL_RenderSetViewport(gRenderer, &viewport);

    // render grid
    
    SDL_Rect rect = {0};
    SDL_QueryTexture(game->gridTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(gRenderer, game->gridTexture, NULL, &rect);

    // render player Tetrimino

    // Tetrimino* player_ttmn = game->gamelogic->player->ttmn;
    // SDL_Rect rect = {0};
    // for(int i = 0 ; i < player_ttmn->tiles_count ; ++i)
    // {
    //     int x = player_ttmn->x + player_ttmn->tiles[i].x;
    //     int y = player_ttmn->y + player_ttmn->tiles[i].y;
    //     SDL_Rect rect = Grid_GetTileRect(x, y, game->tile_size, game->showGrid);

    // }

    // unset viewport

    SDL_RenderSetViewport(gRenderer, NULL);

    // render Tetrimino queue

    // render held Tetrimino

}

void Game_Destroy(Game *game)
{
    SDL_DestroyTexture(game->gridTexture);
    GL_Destroy(game->gamelogic);
    free(game);
    game = NULL;
}

void Game_UpdateGridTexture(Game *game)
{
    // Create Blank Texture
    Grid* grid = game->gamelogic->grid;
    int w = grid->columns * game->tile_size + (game->showGrid?1:0);
    int h = grid->rows * game->tile_size + (game->showGrid?1:0);
    SDL_Texture *texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);

    // Set texture as render target
    SDL_SetRenderTarget(gRenderer, texture);

    // if asked, draw grid

    if( game->showGrid )
    {
        SDL_SetRenderDrawColor(gRenderer, 0x30, 0x30, 0x30, 0xFF);
        for(int i = game->tile_size ; i < w ; i += game->tile_size)
        {
            SDL_RenderDrawLine(gRenderer, i, 0, i, h - 1);
        }
        for(int j = game->tile_size ; j < h ; j += game->tile_size)
        {
            SDL_RenderDrawLine(gRenderer, 0, j, w - 1, j);
        }
    }


    // draw tiles
    // TODO

    // draw outline

    SDL_Rect outline = {0,0, w, h};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(gRenderer, &outline);


    // unset render target
    SDL_SetRenderTarget(gRenderer, NULL);

    // return texture
    game->gridTexture = texture;
}
