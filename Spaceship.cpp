#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* renderer):Object(renderer)
{
	x = (SCREEN_WIDTH / 2) - 50; //- (renderRect.w / 2);
	y = SCREEN_HEIGHT * 0.80;
	width = 100;
	height = 100;
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::Render()
{
    setRectSize(mainHitbox, x + 25, y, 50, height);
    setRectSize(leftHitbox, x, y + 50, 25, 40);
    setRectSize(rightHitbox, x + 75, y + 50, 25, 40);

//	Render Hitbox (for bug fixing only)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &leftHitbox);
	SDL_RenderDrawRect(renderer, &mainHitbox);
	SDL_RenderDrawRect(renderer, &rightHitbox);
}

void SpaceShip::moveUp()
{
    y -= 10;
}

void SpaceShip::moveDown()
{
    y += 10;
}

void SpaceShip::moveLeft()
{
    x -= 10;
}

void SpaceShip::moveRight()
{
    x += 10;
}

SDL_Rect* SpaceShip::getLeftHitBox()
{
    return &leftHitbox;
}

SDL_Rect* SpaceShip::getRightHitBox()
{
    return &rightHitbox;
}

SDL_Rect* SpaceShip::getMainHitBox()
{
    return &mainHitbox;
}
