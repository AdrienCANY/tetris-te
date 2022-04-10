#include "event.h"
#include <stdlib.h>

Event* Event_Create(EventType type, int* data, int data_len)
{
    Event *event = malloc(sizeof(Event));
    event->data = data;
    event->type = type;
    event->data_len = data_len;
    return event;
}

Event *Event_CreateBlank()
{
    Event* event = malloc(sizeof(Event));
    event->data = calloc(10, sizeof(int));
    event->type = 0;
    event->data_len = 0;
    return event;
}

void Event_Destroy(Event *ev)
{
    if(ev->data != NULL)
        free(ev->data);
    free(ev);
    ev = NULL;
}

void Event_AddData(Event *event, int data)
{
    event->data[event->data_len] = data;
    event->data_len++;
}