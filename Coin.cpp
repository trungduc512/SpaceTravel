#include "Coin.h"

Coin::Coin(SDL_Renderer *renderer, unsigned int Count) : MovingObject(renderer)
{
    powerUpType = -1;
    path = "image/coin.png";
    if(Count % POWERUPS_SPAWN_RATE == 0 && Count != 0)
    {
        GetRandomPowerUp();
    }
    getTexture(texture, renderer, path, 0, 0, 0);
    //get renderBox size
    Box.w = 60;
    Box.h = 60;

	// spawning coin randomly base on sreenwidth
    x = rand() % (SCREEN_WIDTH - Box.w);
	y = -100;
	moveSpeed = 10; // default speed = 10
    setRectSize(Box, x, y, Box.w, Box.h);
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
    //render image
    if(powerUpType == -1){
        setRectSize(clipBox,40*((frame/5)%12), 0, 40, 40);
        SDL_RenderCopy(renderer, texture, &clipBox, &Box);
    }
    else if(powerUpType == HEAL){
        setRectSize(clipBox,226 + 800*((frame/10)%4), 0, 350, 350);
        SDL_RenderCopy(renderer, texture, &clipBox, &Box);
    }
    else if(powerUpType == REDUCE_COOLDOWN){
        setRectSize(clipBox,58*((frame/4)%10), 0, 58, 79);
        SDL_RenderCopy(renderer, texture, &clipBox, &Box);
    }
    else{
        SDL_RenderCopy(renderer, texture, NULL, &Box);
    }
    setRectSize(Hitbox, Box.x, Box.y, Box.w, Box.h);
	//Render Collision Box
    //SDL_SetRenderDrawColor(renderer, 255, 255, 102, 255);
    //SDL_RenderDrawRect(renderer, &Hitbox);
}

SDL_Rect* Coin::getHitBox()
{
    return &Hitbox;
}

void Coin::GetRandomPowerUp()
{
    powerUpType = rand()%3;
    if(powerUpType == HEAL){
        path = "image/heart_sprite.png";
    }
    else if(powerUpType == SHIELD){
        path = "image/shield_powerup.png";
    }
    else if(powerUpType == REDUCE_COOLDOWN){
        path = "image/battery_sprite_sheet.png";
    }
}
