#ifndef EVENT_H_
#define EVENT_H_

typedef enum
{
    LINE_COMPLETED,
    TETRIMINO_PLACED,
    GAME_OVER,
    GAME_RESTART
} EventType;

typedef struct 
{
    EventType type;
    int* data;
    int data_len;
} Event;

Event* Event_Create(EventType, int* data, int data_len);
void Event_Destroy(Event*);

#endif