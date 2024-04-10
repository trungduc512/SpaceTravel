#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitBox) : MovingObject(renderer)
{
    getTexture(texture, renderer, "image/bullet.png", 69, 69, 69, width, height);
    moveSpeed = 20;
    x = mainHitBox->x + (mainHitBox->w - width)/2;
    y = mainHitBox->y - height / 1.5;
    setRectSize(Box, x, y, width, height);
}

Bullet::Bullet(SDL_Renderer* renderer, const SDL_Rect *bossHitbox, double angle) : MovingObject(renderer)
{
    getTexture(texture, renderer, "image/Boss_bullet.png", 69, 69, 69, width, height);
    x = bossHitbox->x +  bossHitbox->w / 2 - width/2;
    y = bossHitbox->y + bossHitbox->h / 2;
    setRectSize(Box, x, y, width, height);
    this->angle = angle;
    vX = sin(this->angle);
    vY = cos(this->angle);
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
}

void Bullet::Update()
{
    Box.y -= moveSpeed;
}

void Bullet::UpdateEx()
{
    Box.y += vY * (double)BOSS_BULLET_SPEED;
    Box.x += vX * (double)BOSS_BULLET_SPEED;
}

void Bullet::Render()
{
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
    SDL_RenderCopy(renderer, texture, NULL, &Box);
    //Render Hitbox
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &Hitbox);
}

void Bullet::RenderEx()
{
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
    SDL_RenderCopyEx(renderer, texture, NULL, &Box, 180 - angle * 180 / 3.141592, NULL, SDL_FLIP_NONE);
    //Render Hitbox
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &Hitbox);
    //std::cout << angle << std::endl;
    //std::cout << vX << std::endl;
    //std::cout << vY << std::endl;
}

SDL_Rect* Bullet::getHitBox()
{
    return &Hitbox;
}







