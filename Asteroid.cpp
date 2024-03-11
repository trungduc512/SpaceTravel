#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer *renderer) : MovingObject(renderer)
{
    x = rand() % SCREEN_WIDTH; // spawning asteroid randomly base on sreenwidth
	y = 0;
	moveSpeed = 10; // default speed = 10
    setRectSize(Box, x, y, 80, 80);
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
{
	Box.y += moveSpeed;
}

void Asteroid::Render()
{
	Hitbox.x = Box.x + 20;
	Hitbox.y = Box.y + 20;
	Hitbox.w = 30;
	Hitbox.h = 30;

//	Render Collision Box
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &Hitbox);
}

bool Asteroid::isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox)
{
    if(SDL_HasIntersection(&Hitbox, leftHitBox)) return true;
    if(SDL_HasIntersection(&Hitbox, rightHitBox)) return true;
    if(SDL_HasIntersection(&Hitbox, mainHitBox)) return true;
    return false;
}
