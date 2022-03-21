#include "timer.h"

Timer* Timer_Create()
{
    Timer *t = malloc(sizeof(Timer));

    t->isPaused = 0;
    t->isStarted = 0;

    t->pausedTicks = 0;
    t->startTicks = 0;

    return t;
}


void Timer_Start(Timer *t)
{
    t->isPaused = 0;
    t->isStarted = 1;

    t->pausedTicks = 0;
    t->startTicks = SDL_GetTicks();
}


void Timer_Stop(Timer *t)
{
    t->isStarted = 0;
    t->isPaused = 0;

    t->startTicks = 0;
    t->pausedTicks = 0;
}

void Timer_Resume(Timer *t)
{
    if(t->isStarted && t->isPaused)
    {
        t->isPaused = 0;
        t->startTicks = SDL_GetTicks() - t->pausedTicks;
        t->pausedTicks = 0;
    }
}

void Timer_Pause(Timer *t)
{
    if(t->isStarted && !t->isPaused)
    {
        t->isPaused = 1;
        t->pausedTicks = SDL_GetTicks() - t->startTicks;
        t->startTicks = 0;
    }
}

Uint32 Timer_GetTicks(Timer *t)
{
    Uint32 time = 0;

    if(t->isStarted)
    {
        time = ( t->isPaused ) ? t->pausedTicks : SDL_GetTicks() - t->startTicks;
    }
    
    return time;
}


void Timer_Destroy(Timer *t)
{
    free(t);
    t = NULL;
}