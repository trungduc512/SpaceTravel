#include "Obstacles.h"

Obstacles::Obstacles(SDL_Renderer *renderer, float speed) : MovingObject(renderer)
{
    getRandomImage();
    getTexture(texture, renderer, path, 69, 69, 69, width, height);
    Box.w = width;
    Box.h = height;
    x = rand() % (SCREEN_WIDTH - Box.w);
	y = -100;
	moveSpeed = speed; // default speed = 10
    setRectSize(Box, x, y, Box.w, Box.h);
}

Obstacles::~Obstacles()
{
    SDL_DestroyTexture(texture);
}

void Obstacles::Update()
{
	Box.y += moveSpeed;
}

void Obstacles::Render()
{
    //render image
    SDL_RenderCopy(renderer, texture, NULL, &Box);
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);

	//Render Collision Box (debug)
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &Hitbox);
}

void Obstacles::getRandomImage()
{
    int pathnum = rand() % 100 + 1;
    if(range(pathnum, 1, 40)) path = "image/asteroid(1).png";
    if(range(pathnum, 41, 60)) path = "image/asteroid(2).png";
    if(range(pathnum, 61, 86)) path = "image/asteroid(3).png";
    if(range(pathnum, 87, 92)) path = "image/UFO.png";
    if(range(pathnum, 93, 98)) path = "image/satellite.png";
    if(range(pathnum, 99, 100)) path = "image/amogus.png";
}

SDL_Rect* Obstacles::getHitBox()
{
    return &Hitbox;
}

std::string Obstacles::getPath()
{
    return path;
}
