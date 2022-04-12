#include "seed.h"
#include "utils.h"
#include "constants.h"
#include "global.h"

Seed* Seed_Create()
{
    Seed* seed = malloc(sizeof(Seed));

    seed->prompt = Texture_CreateFromText("Input a seed", gTextFont, gWhite, 1, 0, 100, WINDOW_WIDTH, 100);
    
    seed->seed = Texture_CreateFromText("", gTextFont, gWhite, 0, 250, 200, 300, 100);

    seed->inputs = Texture_CreateFromText("<Esc> = back", gPromptFont, gWhite, 0, 100, 400, 600, 100);

    return seed;
}

void Seed_HandleEvent(Seed *seed, SDL_Event *e)
{
    if(e->type == SDL_QUIT)
    {
        gNextStateID = STATE_EXIT;
    }

    if(e->type == SDL_KEYDOWN )
    {
        if ( e->key.keysym.scancode == SDL_SCANCODE_ESCAPE )
            gNextStateID = STATE_TITLE;
    }
}

void Seed_Render(Seed *seed)
{
    Texture_Render(seed->prompt);
    SDL_SetRenderDrawColor(gRenderer, 0x18, 0x18, 0x18, 0xFF);
    SDL_RenderFillRect(gRenderer, &seed->seed->outer);
    Texture_Render(seed->seed);
    Texture_Render(seed->inputs);
}

void Seed_Destroy(Seed *seed)
{
    Texture_Destroy(seed->prompt);
    Texture_Destroy(seed->seed);
    Texture_Destroy(seed->inputs);
    free(seed);
}