#include "seed.h"
#include "utils.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>
#include "state.h"
#include "global.h"

Seed* Seed_Create()
{
    Seed* seed = malloc(sizeof(Seed));

    seed->prompt = Texture_CreateFromText("Input a seed", gTextFont, gWhite, 1, 0, 100, WINDOW_WIDTH, 100);
    
    seed->seed = Texture_CreateFromText("", gTextFont, gWhite, 0, 250, 200, 300, 100);

    seed->inputs = Texture_CreateFromText("<Esc> = back", gPromptFont, gWhite, 0, 100, 400, 600, 100);

    seed->seed_str = calloc(SEED_LEN + 1, sizeof(char));

    seed->audio_nope = Mix_LoadWAV("../res/hold_fail.wav");

    SDL_StartTextInput();

    return seed;
}

void Seed_HandleEvent(Seed *seed, SDL_Event *e)
{
    // quit event

    if(e->type == SDL_QUIT)
    {
        gNextStateID = STATE_EXIT;
    }

    // key down events

    else if(e->type == SDL_KEYDOWN )
    {
        // escape = go back to title page
        
        if ( e->key.keysym.scancode == SDL_SCANCODE_ESCAPE )
        {
            gNextStateID = STATE_TITLE;
        }
            

        // backspace = remove last character of the seed

        else if( e->key.keysym.scancode == SDL_SCANCODE_BACKSPACE && strlen(seed->seed_str) > 0 )
        {
            seed->seed_str[strlen(seed->seed_str) - 1] = '\0';
            Texture_LoadText(seed->seed, seed->seed_str, 0);
        }

        else if (e->key.keysym.scancode == SDL_SCANCODE_RETURN)
        {
            if(strlen(seed->seed_str) == 4)
            {
                gNextStateID = STATE_GAME;
            }
            else 
            {
                Mix_PlayChannel(-1, seed->audio_nope, 0);
            }
        }
    }

    // text input events

    else if (e->type == SDL_TEXTINPUT)
    {
        if(strlen(seed->seed_str) < 4)
        {
            char c = *e->text.text;
            if('a' <= c && c <= 'z')
            {
                c = toUpper(c);
            }
            if('A' <= c && c <= 'Z')
            {
                strncat(seed->seed_str, &c, 1);
                Texture_LoadText(seed->seed, seed->seed_str, 0);
            }

        }
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
    SDL_StopTextInput();
    free(seed->seed_str);

    Texture_Destroy(seed->prompt);
    Texture_Destroy(seed->seed);
    Texture_Destroy(seed->inputs);
    free(seed);
}

int Seed_GetSeed(Seed *seed)
{
    return  Seed_IsValid(seed) ? getIntFromAlpha(seed->seed_str) : -1;
}

int Seed_IsValid(Seed *seed)
{
    for(int i = 0 ; i < SEED_LEN ; i++)
    {
        char c = seed->seed_str[i];
        if('Z' < c || c < 'A')
            return 0;
    }
    return 1;
}