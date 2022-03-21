#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "state.h"
#include <SDL.h>
#include <SDL_ttf.h>

// game state

extern State gCurrentStateID;
extern State gNextStateID;
extern void* gCurrentState;

// window and renderer

extern SDL_Renderer *gRenderer;
extern SDL_Window *gWindow;

// style

extern TTF_Font *gTitleFont;
extern TTF_Font *gTextFont;
extern SDL_Color gWhite;


int Global_Run();
int Global_Init();
void Global_ChangeState();
void Global_HandleEvent();
void Global_Render();
void Global_Close();


#endif