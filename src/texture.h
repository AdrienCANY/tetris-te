#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct 
{
    SDL_Rect outer;
    SDL_Rect inner;
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Color color;
} Texture;

Texture* Texture_CreateFromText(char* text, TTF_Font *font, SDL_Color color, int wrap, int x, int y, int w, int h);
void Texture_LoadText(Texture* texture, char* text, int wrap);
void Texture_Free(Texture* texture);
void Texture_Render(Texture* texture);
void Texture_Destroy(Texture* texture);

#endif