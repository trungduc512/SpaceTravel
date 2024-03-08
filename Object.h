#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <SDL_image.h>
#include "UsefulFunctions.h"

class Object
{
public:
    Object(SDL_Renderer* renderer);
    ~Object();

    float x;
    float y;
    float width;
    float height;

protected:
    SDL_Renderer* renderer;
};

#endif // OBJECT_H_INCLUDED
