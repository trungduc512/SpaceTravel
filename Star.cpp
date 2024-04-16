#include "Star.h"

Star::Star(SDL_Renderer* renderer, int w, int h, float speed) : MovingObject(renderer)
{
    x = rand() % SCREEN_WIDTH;
	y = 0;
	moveSpeed = speed;
    setRectSize(Box, x, y, w, h);
}

Star::Star(SDL_Renderer* renderer, int typeOfStar, float x, float y) : MovingObject(renderer)
{
    SetPos(x,y);
	if( typeOfStar == STAR ){ // enum from game
        moveSpeed = STAR_MOVE_SPEED;
        width = STAR_SIZE;
        height = STAR_SIZE;
    }
    else{
        moveSpeed = LARGE_STAR_MOVE_SPEED;
        width = LARGE_STAR_SIZE;
        height = LARGE_STAR_SIZE;
    }
    setRectSize(Box, x, y, width, height);
}

Star::~Star()
{
}

void Star::Update()
{
	Box.y += moveSpeed;
}

void Star::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &Box);
}

void Star::SetPos(float x_pos, float y_pos)
{
    x = x_pos;
    y = y_pos;
}
