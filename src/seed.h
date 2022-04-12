#ifndef SEED_H_
#define SEED_H_

#include "texture.h"

typedef struct 
{
    Texture *prompt;
    Texture *seed;
    Texture *inputs;
} Seed;

Seed* Seed_Create();
void Seed_HandleEvent(Seed *seed, SDL_Event *e);
void Seed_Render(Seed *seed);
void Seed_Destroy(Seed *seed);

#endif