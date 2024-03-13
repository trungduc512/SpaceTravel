#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* renderer, std::string path1, std::string path2):Object(renderer)
{
    //get ship image
    SDL_Surface* shipSurface = IMG_Load(path1.c_str());
    SDL_SetColorKey (shipSurface, SDL_TRUE, SDL_MapRGB(shipSurface->format, 69, 69, 69));
    shipTexture = SDL_CreateTextureFromSurface(renderer, shipSurface);
    //get flame spritesheet
    SDL_Surface*  flameSurface = IMG_Load(path2.c_str());
    SDL_SetColorKey (flameSurface, SDL_TRUE, SDL_MapRGB(flameSurface->format, 69, 69, 69));
    flameTexture = SDL_CreateTextureFromSurface(renderer, flameSurface);
    //get the spaceship to the middle of the screen
    renderBox.w = shipSurface->w;
    renderBox.h = shipSurface->h;
    //free unused surface
    SDL_FreeSurface(shipSurface);
    SDL_FreeSurface(flameSurface);
    //set initial position for the spaceship
	x = (SCREEN_WIDTH / 2) - (renderBox.w / 2);
	y = SCREEN_HEIGHT * 0.80;
	//set width and height for the image
	width = 85;
	height = 85;
}

SpaceShip::~SpaceShip()
{
    SDL_DestroyTexture(shipTexture);
    SDL_DestroyTexture(flameTexture);
}

void SpaceShip::Render(unsigned int frame)
{
    setRectSize(renderBox, x, y , width, height);
    setRectSize(flame, x + 30, y + 80, 25, 40);
    setRectSize(clipBox, 140*((frame/5)%8), 0, 140, 260);
    SDL_RenderCopy(renderer, shipTexture, NULL, &renderBox);
    SDL_RenderCopy(renderer, flameTexture, &clipBox, &flame);
    setRectSize(mainHitbox, x + 30, y, 25, 85);
    setRectSize(leftHitbox, x, y + 40, 30, 35);
    setRectSize(rightHitbox, x + 55, y + 40, 30, 35);

//	Render Hitbox (for bug fixing only)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//	SDL_RenderDrawRect(renderer, &flame);
//	SDL_RenderDrawRect(renderer, &leftHitbox);
	SDL_RenderDrawRect(renderer, &mainHitbox);
//	SDL_RenderDrawRect(renderer, &rightHitbox);
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
