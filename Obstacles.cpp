#include "Obstacles.h"

Obstacles::Obstacles(SDL_Renderer *renderer) : MovingObject(renderer)
{
    getRandomImage();
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 69, 69, 69));
    //get texture
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    Box.w = newSurface->w; // this get width from new_surface
    Box.h = newSurface->h;
	SDL_FreeSurface(newSurface);
    x = rand() % (SCREEN_WIDTH - Box.w); // spawning asteroid randomly base on sreenwidth
	y = -100;
	moveSpeed = 10; // default speed = 10
    setRectSize(Box, x, y, Box.w, Box.h);
//    setRectSize(Hitbox, x, y, Box.w, Box.h);
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
	//Render Collision Box
//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//	SDL_RenderDrawRect(renderer, &Hitbox);
}

bool Obstacles::isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox) //move to useful function in the future may be
{
    if(SDL_HasIntersection(&Hitbox, leftHitBox)) return true;
    if(SDL_HasIntersection(&Hitbox, rightHitBox)) return true;
    if(SDL_HasIntersection(&Hitbox, mainHitBox)) return true;
    return false;
}

void Obstacles::getRandomImage()
{
    int pathnum = rand() % 100 + 1;
    if(range(pathnum, 1, 40)) path = "image/asteroid(1).png";
    if(range(pathnum, 41, 96)) path = "image/asteroid(2).png";
    if(range(pathnum, 97, 99)) path = "image/satellite.png";
    if(range(pathnum, 100, 100)) path = "image/amogus.png";
}

SDL_Rect* Obstacles::getHitBox()
{
    return &Hitbox;
}
