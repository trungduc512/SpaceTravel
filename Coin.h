#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "MovingObject.h"
#include <iostream>
#include <cmath>

class Coin : public MovingObject
{
public:
    Coin(SDL_Renderer *renderer, unsigned int Count);
    Coin(SDL_Renderer *renderer, int type, float x_pos, float y_pos);
    ~Coin();

    enum PowerUpType { HEAL, SHIELD, REDUCE_COOLDOWN };
    void Render(unsigned int frame);
    void Update( const SDL_Rect* mainHitBox);
    void GetRandomPowerUp();
    SDL_Rect* getHitBox();
    int powerUpType;
    int getType();
    void setType( int type );

private:
    SDL_Rect Hitbox;
    SDL_Rect clipBox;
    SDL_Texture* texture;
    std::string path;
};

#endif // COIN_H_INCLUDED
