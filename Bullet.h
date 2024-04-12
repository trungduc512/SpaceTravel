#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "MovingObject.h"
#include <cmath>

class Bullet : public MovingObject
{
public:
    Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitbox);
    Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitbox, SDL_Texture* pre_creatingTexture);
    Bullet(SDL_Renderer* renderer, const SDL_Rect *bossHitbox, double angle);
    ~Bullet();

    void Render();
    void Render(unsigned int frame);
    void RenderEx();
    void Update();
    void UpdateEx();
    SDL_Rect* getHitBox();
    bool isSpecialBullet;

private:
    SDL_Rect Hitbox;
    SDL_Rect Clipbox;
    SDL_Rect Renderbox;
    SDL_Texture* texture;
    std::string path;
    double vX,vY;
    double angle;
};

#endif // BULLET_H_INCLUDED
