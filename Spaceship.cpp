#include "SpaceShip.h"
#include "UsefulFunctions.h"

SpaceShip::SpaceShip(SDL_Renderer* renderer):Object(renderer)
{
	x = (SCREEN_WIDTH / 2); //- (renderRect.w / 2);
	y = SCREEN_HEIGHT * 0.80;
	width = 100;
	height = 100;
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::Render()
{
//	mainHitbox.x = x + 25; //default x + 25;
//	mainColliderRect.y = y; //default y
//	mainColliderRect.h = height; //default height
//	mainColliderRect.w = 50; //default 50

    setSizeForHitbox(mainHitbox, x + 25, y, 50, height);
    setSizeForHitbox(leftHitbox, x, y + 50, 25, 40);
    setSizeForHitbox(rightHitbox, x + 75, y + 50, 25, 40);


//	leftColliderRect.x = x;
//	leftColliderRect.y = y + 50;
//	leftColliderRect.h = 40;
//	leftColliderRect.w = 25;
//
//	rightColliderRect.x = x + 75;
//	rightColliderRect.y = y + 50;
//	rightColliderRect.h = 40;
//	rightColliderRect.w = 25;

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
