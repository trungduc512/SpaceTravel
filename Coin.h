#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "MovingObject.h"
#include <iostream>

class Coin : public MovingObject
{
public:
    Coin(SDL_Renderer *renderer, std::string path);
    ~Coin();

    void Render(unsigned int frame);
    void Update();
    bool isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox);

private:
    SDL_Rect Hitbox;
    SDL_Rect clipBox;
    SDL_Texture* texture;
};

#endif // COIN_H_INCLUDED
