#ifndef USEFULFUNCTIONS_H_INCLUDED
#define USEFULFUNCTIONS_H_INCLUDED

#include <SDL.h>

void setSizeForHitbox(SDL_Rect &rect, float x, float y, float w, float h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

#endif // USEFULFUNCTIONS_H_INCLUDED
