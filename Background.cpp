#include "Background.h"

Background::Background(SDL_Renderer* renderer) : MovingObject(renderer)
{
    getRandomBackGround();
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 0, 0));
    //get texture
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    Box.w = newSurface->w;
    Box.h = newSurface->h;
	SDL_FreeSurface(newSurface);
    x = rand() % (SCREEN_WIDTH - Box.w / 2 );
	y = -Box.h;
	moveSpeed = 5;
    setRectSize(Box, x, y, Box.w, Box.h);
}

Background::~Background()
{
    SDL_DestroyTexture(texture);
}

void Background::Update()
{
    Box.y += moveSpeed;
}

void Background::Render()
{
    SDL_RenderCopy(renderer, texture, NULL, &Box);
}

void Background::getRandomBackGround()
{
    int pathnum = rand() % 5 + 1;
    switch(pathnum)
    {
    case 1:
        path = "image/earth.png";
        break;
    case 2:
        path = "image/galaxy(2).png";
        break;
    case 3:
        path = "image/galaxy(1).png";
        break;
    case 4:
        path = "image/planet(2).png";
        break;
    case 5:
        path = "image/planet(1).png";
        break;
    default:
        path = "image/earth.png";
        break;
    }

}
