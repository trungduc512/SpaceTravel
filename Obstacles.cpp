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

Obstacles::Obstacles(SDL_Renderer *renderer, float speed, int type, float x_pos, float y_pos) : MovingObject(renderer)
{
    SetType(type);
    getTexture(texture, renderer, path, 69, 69, 69, width, height);
    Box.w = width;
    Box.h = height;
    SetPos(x_pos,y_pos);
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
    if(range(pathnum, 1, 40)) {
        path = "image/asteroid(1).png";
        obstacleType = 1;
    }
    if(range(pathnum, 41, 60)) {
        path = "image/asteroid(2).png";
        obstacleType = 2;
    }
    if(range(pathnum, 61, 86)) {
        path = "image/asteroid(3).png";
        obstacleType = 3;
    }
    if(range(pathnum, 87, 92)) {
        path = "image/UFO.png";
        obstacleType = 4;
    }
    if(range(pathnum, 93, 98)) {
        path = "image/satellite.png";
        obstacleType = 5;
    }
    if(range(pathnum, 99, 100)) {
        path = "image/amogus.png";
        obstacleType = 6;
    }
}

SDL_Rect* Obstacles::getHitBox()
{
    return &Hitbox;
}

std::string Obstacles::getPath()
{
    return path;
}

int Obstacles::getType()
{
    return obstacleType;
}

void Obstacles::SetPos(float x_pos, float y_pos)
{
    x = x_pos;
    y = y_pos;
}

float Obstacles::getSpeed()
{
    return moveSpeed;
}

void Obstacles::SetType(int type)
{
    if(type == 1) {
        path = "image/asteroid(1).png";
        obstacleType = 1;
    }
    if(type == 2) {
        path = "image/asteroid(2).png";
        obstacleType = 2;
    }
    if(type == 3) {
        path = "image/asteroid(3).png";
        obstacleType = 3;
    }
    if(type == 4) {
        path = "image/UFO.png";
        obstacleType = 4;
    }
    if(type == 5) {
        path = "image/satellite.png";
        obstacleType = 5;
    }
    if(type == 6) {
        path = "image/amogus.png";
        obstacleType = 6;
    }
}
