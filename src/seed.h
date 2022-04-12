#ifndef SEED_H_
#define SEED_H_

#include "texture.h"
#include "SDL_mixer.h"

typedef struct 
{
    Texture *prompt;
    Texture *seed;
    Texture *inputs;
    char *seed_str;
    Mix_Chunk *audio_nope;
} Seed;

Seed* Seed_Create();
void Seed_HandleEvent(Seed *seed, SDL_Event *e);
void Seed_Render(Seed *seed);
int Seed_GetSeed(Seed *seed);
void Seed_Destroy(Seed *seed);

int Seed_IsValid(Seed *seed);

#endif