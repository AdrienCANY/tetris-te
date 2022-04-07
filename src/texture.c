#include "texture.h"
#include "global.h"
#include "utils.h"
#include <stdio.h>

Texture* Texture_CreateFromText(char* text, TTF_Font *font, SDL_Color color, int wrap, int x, int y, int w, int h)
{
    Texture *tx = malloc(sizeof(Texture));

    tx->font = font;
    tx->color = color;
    SDL_Rect outer = {x, y, w, h};
    tx->outer = outer;
    tx->texture = NULL;

    Texture_LoadText(tx, text, wrap);

    return tx;
}

void Texture_LoadText(Texture* tx, char* text, int wrap)
{
    Texture_Free(tx);

    // SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(tx->font, text, tx->color, tx->outer.w);
    SDL_Surface *surface = 
        (wrap) 
        ? TTF_RenderText_Blended_Wrapped(tx->font, text, tx->color, tx->outer.w) 
        : TTF_RenderText_Solid(tx->font, text, tx->color);

    if(surface == NULL)
    {
        printf("Failed to render text into surface ! Message : %s\n", TTF_GetError());
    }
    else
    {
        tx->texture = SDL_CreateTextureFromSurface(gRenderer, surface);

        if(surface->w > tx->outer.w)
        {
            tx->inner.x = tx->outer.x;
            tx->inner.w = tx->outer.w;
        }
        else
        {
            tx->inner.w = surface->w;
            tx->inner.x = tx->outer.x + ( tx->outer.w - tx->inner.w ) / 2;
        }
        if(surface->h > tx->outer.h)
        {
            tx->inner.y = tx->outer.y;
            tx->inner.h = tx->outer.h;
        }
        else
        {
            tx->inner.h = surface->h;
            tx->inner.y = tx->outer.y + ( tx->outer.h - tx->inner.h ) / 2;
        }
    }
    SDL_FreeSurface(surface);
}

void Texture_Free(Texture *tx)
{
    if(tx->texture != NULL)
    {
        SDL_DestroyTexture(tx->texture);
        tx->texture = NULL;
    }
}

void Texture_Render(Texture* texture)
{
    SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(gRenderer, &texture->outer);
    SDL_RenderDrawRect(gRenderer, &texture->outer);
    SDL_RenderCopy(gRenderer, texture->texture, NULL, &texture->inner);
}

void Texture_Destroy(Texture* texture)
{
    Texture_Free(texture);

    free(texture);
    texture = NULL;
}