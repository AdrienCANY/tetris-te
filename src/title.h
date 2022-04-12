#ifndef TITLE_H_
#define TITLE_H_

#include <SDL.h>
#include "texture.h"

typedef struct 
{
    Texture *title;
    Texture *subtitle;
    Texture *play;
    Texture *seed;
} Title;

Title* Title_Create();
void Title_HandleEvent(Title* title, SDL_Event *e);
void Title_Render(Title* title);
void Title_Destroy(Title* title);

#endif