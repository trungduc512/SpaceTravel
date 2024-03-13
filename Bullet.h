#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "MovingObject.h"

class Bullet : public MovingObject
{
public:
    Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitbox);
    ~Bullet();

    void Render();
    void Update();

private:
    SDL_Rect Hitbox;
    SDL_Texture* texture;
    std::string path;
};

#endif // BULLET_H_INCLUDED
