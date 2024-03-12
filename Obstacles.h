#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "MovingObject.h"
#include <iostream>

class Obstacles : public MovingObject
{
public:
    Obstacles(SDL_Renderer *renderer);
    ~Obstacles();

    void Render();
    void Update();
    bool isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox);
    void getRandomImage();

private:
    SDL_Rect Hitbox;
    SDL_Texture* texture;
    std::string path;
};


#endif // ASTEROID_H_INCLUDED
