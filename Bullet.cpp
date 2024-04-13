#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitBox) : MovingObject(renderer)
{
    getTexture(texture, renderer, "image/bullet.png", 69, 69, 69, width, height);
    moveSpeed = 20;
    x = mainHitBox->x + (mainHitBox->w - width)/2;
    y = mainHitBox->y - height / 1.5;
    setRectSize(Box, x, y, width, height);
    isSpecialBullet = 0;
}

Bullet::Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitBox, SDL_Texture* pre_creatingTexture) : MovingObject(renderer)
{
    texture = pre_creatingTexture;
    moveSpeed = 10;
    width = 80;
    height = 120;
    x = mainHitBox->x + (mainHitBox->w - width)/2;
    y = mainHitBox->y - height / 1.5;
    setRectSize(Box, x, y, width, height);
    isSpecialBullet = 1;
}

Bullet::Bullet(SDL_Renderer* renderer, const SDL_Rect *bossHitbox, double angle) : MovingObject(renderer)
{
    getTexture(texture, renderer, "image/boss_bullet_sprite.png", 69, 69, 69);
    width = 48;
    height = 92;
    x = bossHitbox->x +  bossHitbox->w / 2 - width/2;
    y = bossHitbox->y + bossHitbox->h / 2;
    setRectSize(Box, x, y, width, height);
    this->angle = angle;
    vX = sin(this->angle);
    vY = cos(this->angle);
    isSpecialBullet = 0;
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
    setRectSize(Renderbox, Box.x, Box.y, Box.w, Box.h);
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
    SDL_RenderCopy(renderer, texture, NULL, &Box);
    //Render Renderbox
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &Renderbox);
}

void Bullet::Render(unsigned int frame)
{
    setRectSize(Clipbox, (frame % 23) * 244, 0, 244, 365);
    setRectSize(Hitbox, Box.x + Box.w/4, Box.y, Box.w/2, Box.h);
    setRectSize(Renderbox, Box.x, Box.y, Box.w, Box.h);
    SDL_RenderCopy(renderer, texture, &Clipbox, &Box);
    //Render Renderbox
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &Hitbox);
    //SDL_RenderDrawRect(renderer, &Renderbox);
}

void Bullet::RenderEx(unsigned int frame)
{
    setRectSize(Clipbox, ((frame/10) % 5) * 197, 0, 197, 378);
    setRectSize(Renderbox, Box.x, Box.y, Box.w, Box.h);
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
    SDL_RenderCopyEx(renderer, texture, &Clipbox, &Box, 180 - angle * 180 / M_PI, NULL, SDL_FLIP_NONE);
    //Render Renderbox
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







