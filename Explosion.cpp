#include "Explosion.h"

Explosion::Explosion(SDL_Renderer* renderer) : Object(renderer)
{
    std::string path = "image/Explosion.png";
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 69, 69, 69));
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    SDL_FreeSurface(newSurface);
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
