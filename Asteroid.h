#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "MovingObject.h"

class Asteroid : public MovingObject
{
public:
    Asteroid(SDL_Renderer *renderer);
    ~Asteroid();

    void Render();
    void Update();
private:
    SDL_Rect Hitbox;
};


#endif // ASTEROID_H_INCLUDED
