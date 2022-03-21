#ifndef TIMER_H_
#define TIMER_H_

#include <SDL.h>

typedef struct 
{
    Uint32 startTicks;
    Uint32 pausedTicks;

    int isPaused;
    int isStarted;
} Timer;

Timer* Timer_Create();
void Timer_Start(Timer *t);
void Timer_Stop(Timer *t);
void Timer_Resume(Timer *t);
void Timer_Pause(Timer *t);
Uint32 Timer_GetTicks(Timer *t);
void Timer_Destroy(Timer *t);

#endif