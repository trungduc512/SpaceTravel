#include "Coin.h"

Coin::Coin(SDL_Renderer *renderer, std::string path) : MovingObject(renderer)
{
    getTexture(texture, renderer, path, 0, 0, 0);
    //get renderBox size
    Box.w = 60;
    Box.h = 60;

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

SDL_Rect* Coin::getHitBox()
{
    return &Hitbox;
}
