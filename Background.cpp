#include "Background.h"

Background::Background(SDL_Renderer* renderer) : MovingObject(renderer)
{
    getRandomBackGround();
    getTexture(texture, renderer, path, 0, 0, 0, width, height);
    Box.h = height;
    Box.w = width;
    x = rand() % (SCREEN_WIDTH - Box.w / 2 );
	y = -Box.h;
	moveSpeed = 5;
    setRectSize(Box, x, y, Box.w, Box.h);
}

Background::Background(SDL_Renderer* renderer, int type, float x_pos, float y_pos) : MovingObject(renderer)
{
    LoadType(type);
    getTexture(texture, renderer, path, 0, 0, 0, width, height);
    Box.h = height;
    Box.w = width;
    SetPos(x_pos,y_pos);
	moveSpeed = 5;
    setRectSize(Box, x, y, Box.w, Box.h);
}

Background::~Background()
{
    SDL_DestroyTexture(texture);
}

void Background::Update()
{
    Box.y += moveSpeed;
}

void Background::Render()
{
    SDL_RenderCopy(renderer, texture, NULL, &Box);
}

void Background::SetPos( float x_pos, float y_pos)
{
    x = x_pos;
    y = y_pos;
}

void Background::getRandomBackGround()
{
    pathnum = rand() % 8 + 1;
    switch(pathnum)
    {
    case 1:
        path = "image/earth.png";
        break;
    case 2:
        path = "image/galaxy(2).png";
        break;
    case 3:
        path = "image/galaxy(1).png";
        break;
    case 4:
        path = "image/planet(2).png";
        break;
    case 5:
        path = "image/planet(1).png";
        break;
    case 6:
        path = "image/mars.png";
        break;
    case 7:
        path = "image/galaxy(3).png";
        break;
    case 8:
        path = "image/blackhole.png";
        break;
    default:
        path = "image/earth.png";
        break;
    }
}

int Background::getType()
{
    return pathnum;
}

void Background::LoadType(int type)
{
    switch(type)
    {
    case 1:
        path = "image/earth.png";
        break;
    case 2:
        path = "image/galaxy(2).png";
        break;
    case 3:
        path = "image/galaxy(1).png";
        break;
    case 4:
        path = "image/planet(2).png";
        break;
    case 5:
        path = "image/planet(1).png";
        break;
    case 6:
        path = "image/mars.png";
        break;
    case 7:
        path = "image/galaxy(3).png";
        break;
    case 8:
        path = "image/blackhole.png";
        break;
    default:
        path = "image/earth.png";
        break;
    }
}
