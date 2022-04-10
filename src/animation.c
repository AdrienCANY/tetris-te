#include "animation.h"
#include <stdlib.h>

Animation* Anim_Create(Event *event)
{
    Animation *anim = malloc(sizeof(Animation));
    anim->event = event;
    anim->frame = 0;
    return anim;
}

void Anim_Destroy(Animation *anim)
{
    Event_Destroy(anim->event);
    free(anim);
    anim = NULL;
}