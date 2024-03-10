#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* renderer, std::string path):Object(renderer)
{
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey (newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 69, 69, 69));
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    //get the spaceship to the middle of the screen
    renderBox.w = newSurface->w;
    SDL_FreeSurface(newSurface);
	x = (SCREEN_WIDTH / 2) - (renderBox.w / 2);
	y = SCREEN_HEIGHT * 0.80;
	width = 85;
	height = 85;
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::Render()
{
    SDL_RenderCopy(renderer, texture, NULL, &renderBox);
    setRectSize(renderBox, x, y, width, height);
    setRectSize(mainHitbox, x + 30, y, 25, 85);
    setRectSize(leftHitbox, x, y + 40, 30, 35);
    setRectSize(rightHitbox, x + 55, y + 40, 30, 35);

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
