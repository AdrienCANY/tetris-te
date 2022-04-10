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

void Event_Destroy(Event *ev)
{
    free(ev);
    ev = NULL;
}