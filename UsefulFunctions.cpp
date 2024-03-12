#include "UsefulFunctions.h"

void setRectSize(SDL_Rect &rect, float x, float y, float w, float h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

bool range(int &compare, const int min, const int max)
{
    if (compare >= min && compare <= max)
        return 1;
    return 0;
}
