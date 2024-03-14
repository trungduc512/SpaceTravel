#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, const SDL_Rect *mainHitBox) : MovingObject(renderer)
{
    path = "image/bullet.png";
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 69, 69, 69));
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    width = newSurface->w;
    height = newSurface->h;
    SDL_FreeSurface(newSurface);
    moveSpeed = 15;
    x = mainHitBox->x + (mainHitBox->w - width)/2;
    y = mainHitBox->y - height / 1.5;
    setRectSize(Box, x, y, width, height);
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
}

void Bullet::Update()
{
    Box.y -= moveSpeed;
}

void Bullet::Render()
{
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
    SDL_RenderCopy(renderer, texture, NULL, &Box);
    //Render Hitbox
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderDrawRect(renderer, &Hitbox);
}






