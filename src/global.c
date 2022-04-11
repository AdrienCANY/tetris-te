#include "global.h"
#include <SDL.h>
#include <stdio.h>
#include "constants.h"
#include "title.h"
#include "game.h"
#include <SDL_mixer.h>
#include <stdlib.h>

// global variables related to game state

State gCurrentStateID;
State gNextStateID;
void* gCurrentState;

// global variables related to display

SDL_Renderer *gRenderer;
SDL_Window *gWindow;

// style

TTF_Font *gTitleFont;
TTF_Font *gTextFont;
TTF_Font *gPromptFont;
SDL_Color gWhite;

int Global_Init()
{
    int result = 1;
    // initializing libraries 

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Failed to initialize SDL. Message : %s\n", SDL_GetError());
        result = 0;
    }

    if(TTF_Init() < 0)
    {
        printf("Failed to initialize TTF. Message : %s\n", TTF_GetError());
        result = 0;
    }

    // initialize window and renderer

    gWindow = SDL_CreateWindow(WINDOW_TITLE,  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        printf("Failed to create window. Message : %s\n", SDL_GetError());
        result = 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL)
    {
        printf("Failed to create renderer. Message : %s\n", SDL_GetError());
        result = 0;
    }

    // Initialize SDL_Mixer

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf("Failed to initialize mixer. Message %s\n", Mix_GetError());
        result = 0;
    }

    // initializing style variables

    gTitleFont = TTF_OpenFont(FONT_PATH, FONT_SIZE_TITLE);
    gTextFont = TTF_OpenFont(FONT_PATH, FONT_SIZE_TEXT);
    gPromptFont = TTF_OpenFont(FONT_PATH, FONT_SIZE_PROMPT);

    gWhite.r = 0xFF;
    gWhite.g = 0xFF;
    gWhite.b = 0xFF;
    gWhite.a = 0xFF;

    // initializing game state variables

    gCurrentStateID = STATE_TITLE;
    gNextStateID = STATE_NULL;
    gCurrentState = (void*) Title_Create();


    return result;
}


void Global_ChangeState()
{
    if( gNextStateID == STATE_NULL)
        return;

    switch(gCurrentStateID)
    {
        case STATE_TITLE: Title_Destroy( (Title*) gCurrentState ); break;
        case STATE_GAME: Game_Destroy( (Game*) gCurrentState ); break;
    }

    switch(gNextStateID)
    {
        case STATE_TITLE: gCurrentState = (void*) Title_Create(); break;
        case STATE_GAME: gCurrentState = (void*) Game_Create(); break;
    }

    gCurrentStateID = gNextStateID;
    gNextStateID = STATE_NULL;
}


void Global_HandleEvent()
{
    SDL_Event e;

    while( SDL_PollEvent(&e) )
    {
        switch(gCurrentStateID)
        {
            case STATE_TITLE: Title_HandleEvent( (Title*) gCurrentState, &e ); break;
            case STATE_GAME: Game_HandleEvent( (Game*) gCurrentState, &e ); break;
        }
    }

}

void Global_Render()
{
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);

    switch(gCurrentStateID)
    {
        case STATE_TITLE: Title_Render( (Title*) gCurrentState ); break;
        case STATE_GAME: Game_Render( (Game*) gCurrentState ); break;
    }

    SDL_RenderPresent(gRenderer);
}

void Global_Close()
{
    TTF_CloseFont(gTitleFont);
    TTF_CloseFont(gTextFont);
    TTF_CloseFont(gPromptFont);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Global_Logic()
{
    switch(gCurrentStateID)
    {
        case STATE_GAME: Game_Logic( (Game*) gCurrentState ); break;
    } 
}

int Global_Run()
{
    if( !Global_Init() )
    {
        printf("Failed to initialize program.\n");
        return EXIT_FAILURE;
    }

    while( gCurrentStateID != STATE_EXIT )
    {
        Global_HandleEvent();
        Global_Logic();
        Global_Render();
        Global_ChangeState();
    }

    Global_Close();
    return EXIT_SUCCESS;
}