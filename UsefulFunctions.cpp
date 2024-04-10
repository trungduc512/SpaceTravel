#include "UsefulFunctions.h"

void setRectSize(SDL_Rect &rect, float x, float y, float w, float h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

bool range(int &compare, const int min, const int max)
{
    if (compare >= min && compare <= max)
        return 1;
    return 0;
}

void getTexture( SDL_Texture* &texture, SDL_Renderer* renderer, std::string path, Uint8 r, Uint8 g, Uint8 b )
{
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, r, g, b));
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    SDL_FreeSurface(newSurface);
}

void getTexture( SDL_Texture* &texture, SDL_Renderer* renderer, std::string path, Uint8 r, Uint8 g, Uint8 b , float &width, float &height)
{
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, r, g, b));
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    width = newSurface->w;
    height = newSurface->h;
	SDL_FreeSurface(newSurface);
}
