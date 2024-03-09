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
    bool isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox);
private:
    SDL_Rect Hitbox;
};


#endif // ASTEROID_H_INCLUDED
