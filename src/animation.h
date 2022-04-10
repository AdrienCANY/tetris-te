#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "event.h"

typedef struct 
{
    Event *event;
    int frame;
} Animation;

Animation* Anim_Create(Event *event);
void Anim_Destroy(Animation*);

#endif