#include "game.h"
#include "global.h"
#include "constants.h"
#include "utils.h"
#include <time.h>
#include "texture.h"
#include <stdlib.h>
#include <stdio.h>

Game* Game_Create()
{
    Game *game = malloc(sizeof(Game));

    game->gamelogic = GL_Create(20, 10, 3, time(NULL));
    game->showGrid = 1;
    game->tile_size = TILE_SIZE;
    Game_UpdateGridTexture(game);

    // queue
    int next_text_h = 0;
    game->queueFrame = (SDL_Rect) { 425, 100, 150, 0 };
    game->nextTexture = Texture_CreateFromText("NEXT", gTextFont, gWhite, 0, game->queueFrame.x, game->queueFrame.y, 150, 20); 
    SDL_QueryTexture(game->nextTexture->texture, NULL, NULL, NULL, &next_text_h);
    game->queueRects[0] = (SDL_Rect) {
        game->queueFrame.x,
        game->queueFrame.y + next_text_h,
        game->queueFrame.w,
        3*game->tile_size
    };
    for(int i = 1 ; i < GAME_QUEUE_SIZE ; ++i)
    {
        game->queueRects[i] = (SDL_Rect){
            game->queueFrame.x,
            game->queueRects[i-1].y + game->queueRects[i-1].h, 
            game->queueFrame.w,
            3*game->tile_size
        };
    }
    game->queueFrame.h = game->queueRects[GAME_QUEUE_SIZE-1].y + game->queueRects[GAME_QUEUE_SIZE-1].h - game->queueFrame.y;



    // hold
    game->holdFrame = (SDL_Rect) {25, 100, 150, 150};
    game->holdTexture = Texture_CreateFromText("HOLD", gTextFont, gWhite, 0, game->holdFrame.x, game->holdFrame.y, 150, 20);
    int hold_h = 0;
    SDL_QueryTexture(game->holdTexture->texture, NULL, NULL, NULL, &hold_h);
    game->holdRect.y = game->holdFrame.y + hold_h;
    game->holdRect.h = game->holdFrame.h - hold_h;
    game->holdRect.x = game->holdFrame.x;
    game->holdRect.w = game->holdFrame.w;
    
    // prompt
    game->promptTexture = Texture_CreateFromText("Press <Space> to start the game or <Esc> to go back to title page", gPromptFont, gWhite, 1, 100, 500, 600, 100 );

    // line count
    char text[15] = "";
    sprintf(text, "LINES: %03d", game->gamelogic->lines_count);
    game->line_count_texture = Texture_CreateFromText(text, gTextFont, gWhite, 0, 425, 475, 150, 25);

    // animation

    game->animation = NULL;

    return game;
}

void Game_HandleEvent(Game* game, SDL_Event *e)
{
    // quit

    if(e->type == SDL_QUIT)
    {
        gNextStateID = STATE_EXIT; // exit the program 
    }

    // key down

    else if( e->type == SDL_KEYDOWN)
    {   
        GameLogic *logic = game->gamelogic;
        SDL_Scancode code = e->key.keysym.scancode;

        // game not started
        
        if( ! GL_IsStarted(logic))
        {
            if(GL_IsGameOver(game->gamelogic))
            {
                if(code == SDL_SCANCODE_SPACE)
                {
                    Game_UpdatePromptText(game, "Press <Space> to start the game or <Esc> to go back to title page");
                    GL_Restart(game->gamelogic);
                }
                else if (code == SDL_SCANCODE_ESCAPE)
                {
                    gNextStateID = STATE_TITLE;
                }
            }
            else
            {
                if( code == SDL_SCANCODE_SPACE )
                {
                    if(!logic->game_over)
                        GL_Start(logic);                
                    else 
                        GL_Restart(logic);
                    Game_UpdatePromptText(game, "");
                }    
            }
            

        }

        // game paused
        else if( GL_IsPaused(logic) )
        {
            switch(code)
            {
                case SDL_SCANCODE_ESCAPE: 
                    gNextStateID = STATE_TITLE;
                    break;
                case SDL_SCANCODE_SPACE:
                    GL_Resume(logic);
                    Game_UpdatePromptText(game, "");
                    break;   
            }
        }

        // game live

        else
        {
            // pausing
            
            if(code == SDL_SCANCODE_ESCAPE)
            {
                Game_UpdatePromptText(game, "Game is paused. Press <Esc> to go back to title page or <Space> to resume the game.");
                GL_Pause(logic);
            }
            
            // inputs related to gameplay
            
            else
            {
                SDL_Scancode *controls = game->gamelogic->player->controls; 
    
                int dx = 0, dy = 0;

                if(code == controls[CONTROL_SOFT_DROP])
                    GL_StartSoftDrop(game->gamelogic);         
                else if( code == controls[CONTROL_HARD_DROP] )
                    GL_HardDrop(game->gamelogic);
                else if (code == controls[CONTROL_LEFT])
                    dx = -1;
                else if (code == controls[CONTROL_RIGHT])
                    dx = 1;
                else if (code == controls[CONTROL_ROTATE_CLOCKWISE])
                    GL_RotatePlayer(game->gamelogic, 1);
                else if (code == controls[CONTROL_ROTATE_COUNTER_CLOCKWISE])
                    GL_RotatePlayer(game->gamelogic, 0);
                else if (code == controls[CONTROL_HOLD])
                    GL_HoldTTMN(game->gamelogic);
                       
                if(dx || dy)
                    GL_MovePlayer(game->gamelogic, dx, dy);
            }
        }
    }

    // key up

    else if (e->type == SDL_KEYUP)
    {
        SDL_Scancode code = e->key.keysym.scancode;
        SDL_Scancode *controls = game->gamelogic->player->controls;
        
        if( code == controls[CONTROL_SOFT_DROP] )
            GL_StopSoftDrop(game->gamelogic);
    }
}

void Game_Render(Game *game)
{
    // set render viewport for grid elements

    int w = game->gamelogic->grid->columns * TILE_SIZE + game->showGrid;
    int h = game->gamelogic->grid->rows * TILE_SIZE + game->showGrid;
    SDL_Rect viewport = {200, 100, w, h};
    SDL_RenderSetViewport(gRenderer, &viewport);

    // render grid
    
    SDL_Rect rect = {0};
    SDL_QueryTexture(game->gridTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(gRenderer, game->gridTexture, NULL, &rect);

    // render shadow

    Tetrimino* shadow = GL_GetLandingShadow(game->gamelogic);
    int shadow_x = shadow->x * game->tile_size;
    int shadow_y = shadow->y * game->tile_size;
    Game_RenderTTMN_Grid(game, shadow, shadow_x, shadow_y);

    // render player Tetrimino

    Tetrimino* player_ttmn = game->gamelogic->player->ttmn;    
    
    int player_display_x = (player_ttmn->x * game->tile_size); //+ (game->showGrid ? 1 : 0);
    int player_display_y = (player_ttmn->y * game->tile_size); //+ (game->showGrid ? 1 : 0);
    Game_RenderTTMN_Grid(game, player_ttmn, player_display_x, player_display_y);

    // animations
    if(game->animation != NULL)
    {
        switch(game->animation->event->type)
        {
            case EVENT_LINE_COMPLETED:
                
                // draw the tetrimino that was placed (yeah we resort to that because of bad design)
                Tetrimino* ev_ttmn = game->animation->event->ttmn;
                Game_RenderTTMN_Grid(game, ev_ttmn, ev_ttmn->x * game->tile_size, game->tile_size * ev_ttmn->y);

                // draw an expanding white rectangle on the rows to be deleted

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                for(int i = 0 ; i < game->animation->event->data_len ; i++)
                {
                    int middle = (game->gamelogic->grid->columns/2) * game->tile_size;
                    int offset = game->showGrid ? 1 : 0;
                    int len = (game->animation->frame/5) * game->tile_size;
                    SDL_Rect anim_rect = { 
                        middle - len + offset,
                        game->animation->event->data[i] * game->tile_size + offset,
                        len * 2,
                        game->tile_size - offset
                    };
                    SDL_RenderFillRect(gRenderer, &anim_rect);
                }   
                
                break;
            
            case EVENT_GAME_RESTART:

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                Grid* grid = game->gamelogic->grid;

                int f = game->animation->frame / 2;
                SDL_Rect anim_rect = {
                    0,
                    (grid->rows - f) * game->tile_size,
                    grid->columns * game->tile_size,
                    f * game->tile_size
                };
                SDL_RenderFillRect(gRenderer, &anim_rect);

                break;
        }
    }

    // unset viewport

    SDL_RenderSetViewport(gRenderer, NULL);

    // render Tetrimino queue

    Texture_Render(game->nextTexture);
    SDL_Rect q_rect = {0};
    for(int i = 0 ; i < game->gamelogic->queue_size ; ++i)
    {
        Tetrimino* q_ttmn = game->gamelogic->queue[i];
        Game_RenderTTMN(game, q_ttmn, game->queueRects[i]);
    }
    
    // render held Tetrimino

    Texture_Render(game->holdTexture);
    if(game->gamelogic->hold != NULL)
    {
        Game_RenderTTMN(game, game->gamelogic->hold, game->holdRect);
    }
        

    // render prompt

    Texture_Render(game->promptTexture);

    // Render queue and hold frame

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &game->queueFrame);
    SDL_RenderDrawRect(gRenderer, &game->holdFrame);

    // render line count

    Texture_Render(game->line_count_texture);

}

void Game_RenderTTMN_Grid(Game *game, Tetrimino* ttmn, int x, int y)
{
    setRenderDrawColor(ttmn->color);
    SDL_Rect rect = {0};
    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        rect = Game_GetTileRenderRect(game, ttmn->tiles[i].x, ttmn->tiles[i].y);
        rect.x += x;
        rect.y += y;
        SDL_RenderFillRect(gRenderer, &rect);
    }
}

void Game_RenderTTMN(Game *game, Tetrimino* ttmn, SDL_Rect dest)
{
    setRenderDrawColor(ttmn->color);
    SDL_RenderSetViewport(gRenderer, &dest);
    
    int offset_x = ttmn->tiles[0].x;
    int offset_y = ttmn->tiles[0].y;

    for(int i = 1; i < ttmn->tiles_count ; ++i)
    {
        offset_x = min(offset_x, ttmn->tiles[i].x);
        offset_y = min(offset_y, ttmn->tiles[i].y);
    }

    int padding_x = ( dest.w - ( game->tile_size * (ttmn->w) ) ) / 2; 
    int padding_y = ( dest.h - ( game->tile_size * (ttmn->h) ) ) / 2;
    SDL_Rect rect = {0};

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        rect = Game_GetTileRenderRect(game, ttmn->tiles[i].x - offset_x, ttmn->tiles[i].y - offset_y);
        rect.x += padding_x;
        rect.y += padding_y;
        SDL_RenderFillRect(gRenderer, &rect);
    }

    SDL_RenderSetViewport(gRenderer, NULL);
}

void Game_Destroy(Game *game)
{
    Texture_Destroy(game->nextTexture);
    Texture_Destroy(game->holdTexture);
    Texture_Destroy(game->line_count_texture);
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
   
    for(int y = 0 ; y < grid->rows ; ++y)
    {
        for(int x = 0 ; x < grid->columns ; ++x)
        {
            setRenderDrawColor(Grid_GetTileColor(grid, x, y));
            SDL_Rect tile_rect = Game_GetTileRenderRect(game, x, y);
            SDL_RenderFillRect(gRenderer, &tile_rect);
        }
    }

    // draw outline

    SDL_Rect outline = {0,0, w, h};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(gRenderer, &outline);


    // unset render target
    SDL_SetRenderTarget(gRenderer, NULL);

    // return texture
    game->gridTexture = texture;

    // update grid dimension
    SDL_QueryTexture(game->gridTexture, NULL, NULL, &game->grid_w, &game->grid_h);
}   


SDL_Rect Game_GetTileRenderRect(Game *game, int x, int y)
{
    SDL_Rect rect = 
    {
        x * game->tile_size + (game->showGrid ? 1 : 0),
        y * game->tile_size + (game->showGrid ? 1 : 0),
        game->tile_size - (game->showGrid ? 1 : 0),
        game->tile_size - (game->showGrid ? 1 : 0)
    };

    return rect;
}

void Game_Logic(Game *game)
{
    GL_Update(game->gamelogic);

    // handle events coming from the logic struct

    Event* event = game->gamelogic->event; 

    if( event != NULL )
    {
        switch(event->type)
        {
            case EVENT_TETRIMINO_PLACED:
                printf("Event caught : Tetrimino placed\n");
                Game_UpdateGridTexture(game);
                Event_Destroy(event);
                break;
            
            case EVENT_LINE_COMPLETED:
                printf("Event caught : line completed\n");
                game->animation = Anim_Create(event);
                GL_Pause(game->gamelogic);
                break;
            
            case EVENT_GAME_OVER:
                printf("Event caught : game over\n");
                Event_Destroy(event);
                break;
            
            case EVENT_GAME_RESTART:
                printf("Event caught : game restarted\n");
                game->animation = Anim_Create(event);
                break;
        }

        // remove event from logic's side
        game->gamelogic->event = NULL;

    }

    // if an animation is ongoing
    if(game->animation != NULL)
    {
        game->animation->frame++;
        switch(game->animation->event->type)
        {
            case EVENT_LINE_COMPLETED:
                if(game->animation->frame/5 > game->gamelogic->grid->columns / 2)
                {
                    char text[15] = "";
                    sprintf(text, "LINES: %03d", game->gamelogic->lines_count);
                    Texture_LoadText(game->line_count_texture, text, 0);
                    Anim_Destroy(game->animation);
                    game->animation = NULL;
                    Game_UpdateGridTexture(game);
                    GL_Resume(game->gamelogic);
                }  
                break;

            case EVENT_GAME_RESTART:

                if(game->animation->frame / 2 > game->gamelogic->grid->rows)
                {
                    Anim_Destroy(game->animation);
                    game->animation = NULL;
                    Game_UpdateGridTexture(game);
                    char text[15] = "";
                    sprintf(text, "LINES: %03d", game->gamelogic->lines_count);
                    Texture_LoadText(game->line_count_texture, text, 0);
                    Game_UpdatePromptText(game, "Press <Space> to start the game or <Esc> to go back to title page");
                }

                break;
        }
    }

    // if game over
    if(GL_IsGameOver(game->gamelogic))
    {
        Game_UpdatePromptText(game, "Game Over :( Press <Esc> to go back to title page or <Space> to start a new game.");
    }
}

void Game_UpdatePromptText(Game *game, char* text)
{
    Texture_LoadText(game->promptTexture, text, 1);
}

void Game_Pause(Game* game)
{
    Game_UpdatePromptText(game, "Game is paused. Press <Esc> to go back to title screen, or <Space> to resume.");
    GL_Pause(game->gamelogic);
}