#ifndef EVENT_H_
#define EVENT_H_

#include "tetrimino.h"

typedef enum
{
    EVENT_LINE_COMPLETED,
    EVENT_TETRIMINO_PLACED,
    EVENT_GAME_OVER,
    EVENT_GAME_RESTART,
    EVENT_HOLD_TETRIMINO
} EventType;

typedef struct 
{
    EventType type;
    int* data;
    int data_len;
    Tetrimino* ttmn;
} Event;

Event* Event_Create(EventType, int* data, int data_len);
Event *Event_CreateBlank();
void Event_RemoveData(Event *event);
void Event_AddData(Event *event, int data);
void Event_Destroy(Event*);

#endif