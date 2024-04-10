#include "Explosion.h"

Explosion::Explosion(SDL_Renderer* renderer) : Object(renderer)
{
    getTexture(texture, renderer, "image/Explosion.png", 69, 69, 69);
}

Explosion::~Explosion()
{
    SDL_DestroyTexture(texture);
}

void Explosion::Render(int i, const SDL_Rect *pos)
{
    SDL_Rect explodeRect;
    setRectSize(explodeRect, pos->x - pos->w / 2, pos->y - pos->h / 2, pos->w * 2, pos->h * 2);
    setRectSize(renderClip, i * 100, 0, 100, 96);
    SDL_RenderCopy(renderer, texture, &renderClip, &explodeRect);
}

