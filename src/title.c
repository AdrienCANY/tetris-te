#include "title.h"
#include <stdio.h>
#include "global.h"
#include "constants.h"

Title* Title_Create()
{
    Title* title = malloc(sizeof(Title));


    title->title = Texture_CreateFromText("Tetris-te", gTitleFont, gWhite, 0, 0, 200, WINDOW_WIDTH, 50);
    title->subtitle = Texture_CreateFromText("by Prankeur_XD", gTextFont, gWhite, 0, 0, 270, WINDOW_WIDTH, 25);
    title->play = Texture_CreateFromText("1: Play", gTextFont, gWhite, 0, 0, 400, WINDOW_WIDTH, 25);
    title->seed = Texture_CreateFromText("2: Seed", gTextFont, gWhite, 0, 0, 425, WINDOW_WIDTH, 25);

    return title;
}


void Title_HandleEvent(Title* title, SDL_Event *e)
{
    if(e->type == SDL_QUIT)
    {
        gNextStateID = STATE_EXIT;
    }
    else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_1)
    {
        gNextStateID = STATE_GAME;
    }
    else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_2)
    {
        gNextStateID = STATE_SEED;
    }
}

void Title_Render(Title* title)
{
    Texture_Render(title->title);
    Texture_Render(title->subtitle);
    Texture_Render(title->play);
    Texture_Render(title->seed);
}

void Title_Destroy(Title* title)
{
    Texture_Destroy(title->title);
    Texture_Destroy(title->subtitle);
    Texture_Destroy(title->play);
    Texture_Destroy(title->seed);
    free(title);
    title = NULL;
}