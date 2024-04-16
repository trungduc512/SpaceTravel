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
    Bullet(SDL_Renderer* renderer, double angle, float x_pos, float y_pos);
    Bullet(SDL_Renderer* renderer, float x_pos, float y_pos);
    ~Bullet();

    void Render();
    void Render(unsigned int frame);
    void RenderEx(unsigned int frame);
    void Update();
    void UpdateEx();
    SDL_Rect* getHitBox();
    bool isSpecialBullet;
    double vX,vY;
    double angle;

private:
    SDL_Rect Hitbox;
    SDL_Rect Clipbox;
    SDL_Rect Renderbox;
    SDL_Texture* texture;
    std::string path;
};

#endif // BULLET_H_INCLUDED
