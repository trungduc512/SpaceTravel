#include "Coin.h"

Coin::Coin(SDL_Renderer *renderer, std::string path) : MovingObject(renderer)
{
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 0, 0));
    //get texture
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    //get renderBox size
    Box.w = 60;
    Box.h = 60;

	SDL_FreeSurface(newSurface);

	// spawning coin randomly base on sreenwidth
    x = rand() % (SCREEN_WIDTH - Box.w);
	y = -100;
	moveSpeed = 10; // default speed = 10
    setRectSize(Box, x, y, Box.w, Box.h);
//    setRectSize(Hitbox, x, y, Box.w, Box.h);
}

Coin::~Coin()
{
    SDL_DestroyTexture(texture);
}

void Coin::Update()
{
	Box.y += moveSpeed;
}

void Coin::Render( unsigned int frame )
{
    setRectSize(clipBox,40*((frame/5)%12), 0, 40, 40);
    //render image
    SDL_RenderCopy(renderer, texture, &clipBox, &Box);
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
	//Render Collision Box
    //SDL_SetRenderDrawColor(renderer, 255, 255, 102, 255);
    //SDL_RenderDrawRect(renderer, &Hitbox);
}

bool Coin::isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox)
{
    if(SDL_HasIntersection(&Hitbox, leftHitBox)) return true;
    if(SDL_HasIntersection(&Hitbox, rightHitBox)) return true;
    if(SDL_HasIntersection(&Hitbox, mainHitBox)) return true;
    return false;
}
