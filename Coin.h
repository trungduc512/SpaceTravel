#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "MovingObject.h"
#include <iostream>

class Coin : public MovingObject
{
public:
    Coin(SDL_Renderer *renderer, unsigned int Count);
    ~Coin();

    enum PowerUpType { HEAL, SHIELD };
    void Render(unsigned int frame);
    void Update();
    void GetRandomPowerUp();
    SDL_Rect* getHitBox();
    int powerUpType;

private:
    SDL_Rect Hitbox;
    SDL_Rect clipBox;
    SDL_Texture* texture;
    std::string path;
};

#endif // COIN_H_INCLUDED
