#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "Object.h"

class Explosion : public Object
{
public:
    Explosion(SDL_Renderer* renderer);
    ~Explosion();

    void Render(int i, const SDL_Rect* pos);

private:
    SDL_Texture* texture;
    SDL_Rect renderBox;
    SDL_Rect renderClip;
};

#endif // EXPLOSION_H_INCLUDED
