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

Coin::Coin(SDL_Renderer *renderer, int type, float x_pos, float y_pos) : MovingObject(renderer)
{
    setType(type);

    getTexture(texture, renderer, path, 0, 0, 0);
    //get renderBox size
    Box.w = 60;
    Box.h = 60;

	// spawning coin randomly base on sreenwidth
    x = x_pos;
	y = y_pos;
	moveSpeed = 10; // default speed = 10
    setRectSize(Box, x, y, Box.w, Box.h);
}

Coin::~Coin()
{
    SDL_DestroyTexture(texture);
}

void Coin::Update( const SDL_Rect* mainHitbox)
{
    float distance = sqrt(pow((mainHitbox->x - Box.x),2) + pow((mainHitbox->y - Box.y),2));
    if(distance < 200){
        float dX = (mainHitbox->x - Box.x) / distance * 20;
        float dY = (mainHitbox->y - Box.y) / distance * 20;
        Box.x += dX;
        Box.y += dY;
    }
    else
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
        setRectSize(clipBox,(frame%22)*126, 0, 126, 126);
        SDL_RenderCopy(renderer, texture, &clipBox, &Box);
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
//    powerUpType = 1;
    if(powerUpType == HEAL){
        path = "image/heart_sprite.png";
    }
    else if(powerUpType == SHIELD){
        path = "image/shield_powerup_sprite.png";
    }
    else if(powerUpType == REDUCE_COOLDOWN){
        path = "image/battery_sprite_sheet.png";
    }
}

void Coin::setType( int type )
{
    powerUpType = type;
    if(type == -1){
        path = "image/coin.png";
    }
    else if(type == HEAL){
        path = "image/heart_sprite.png";
    }
    else if(type == SHIELD){
        path = "image/shield_powerup_sprite.png";
    }
    else if(type == REDUCE_COOLDOWN){
        path = "image/battery_sprite_sheet.png";
    }
}

int Coin::getType()
{
    return powerUpType;
}
