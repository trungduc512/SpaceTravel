#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* renderer, std::string path1, std::string path2):Object(renderer)
{
    getTexture(shipTexture, renderer, path1, 69, 69, 69, width, height);
    getTexture(flameTexture, renderer, path2, 69, 69, 69);
    getTexture(shieldTexture, renderer, "image/shield.png", 69, 69, 69);
    renderBox.w = width;
    renderBox.h = height;

    //set initial position for the spaceship
	x = (SCREEN_WIDTH / 2) - (85 / 2);
	y = SCREEN_HEIGHT * 0.80;

	//set width and height for the image
	width = 85;
	height = 85;
	shielded = 0;
	died = 0;
	reduceCooldown = 0;
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

    //Render Hitbox (for bug fixing only)
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &flame);
    //SDL_RenderDrawRect(renderer, &leftHitbox);
    //SDL_RenderDrawRect(renderer, &mainHitbox);
    //SDL_RenderDrawRect(renderer, &rightHitbox);
}

void SpaceShip::RenderShield()
{
    setRectSize(renderBox2, x - width*0.125, y - height*0.125, width * 1.25, height * 1.25);
    SDL_RenderCopy(renderer, shieldTexture, NULL, &renderBox2);
}

void SpaceShip::moveUp()
{
    y -= SPACESHIP_MOVE_SPEED;
}

void SpaceShip::moveDown()
{
    y += SPACESHIP_MOVE_SPEED;
}

void SpaceShip::moveLeft()
{
    x -= SPACESHIP_MOVE_SPEED;
}

void SpaceShip::moveRight()
{
    x += SPACESHIP_MOVE_SPEED;
}

int SpaceShip::RemainCooldown()
{
    if(lastShootTime == 0){
        return SHOOT_COOLDOWN;
    }
    Uint32 currentTime = SDL_GetTicks();
    int remainCooldown = currentTime - lastShootTime;
    if(remainCooldown >= SHOOT_COOLDOWN){
        return SHOOT_COOLDOWN;
    }
    return remainCooldown;
}

int SpaceShip::RemainCooldownSpecial()
{
    if(lastSpecialShoot == 0){
        return SPECIAL_COOLDOWN;
    }
    Uint32 currentTime = SDL_GetTicks();
    int remainCooldown = currentTime - lastSpecialShoot + reduceCooldown;
    if(remainCooldown >= SPECIAL_COOLDOWN){
        return SPECIAL_COOLDOWN;
    }
    return remainCooldown;
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

bool SpaceShip::isCollided(const SDL_Rect *Hitbox)
{
    if(SDL_HasIntersection(Hitbox, &leftHitbox))return true;
    if(SDL_HasIntersection(Hitbox, &leftHitbox)) return true;
    if(SDL_HasIntersection(Hitbox, &mainHitbox)) return true;
    return false;
}

void SpaceShip::PowerUp(int powerup)
{
    if(powerup == SHIELD){
        shielded = true;
    }
    if(powerup == HEAL){
        livesLeft++;
        if(livesLeft > 3){
            livesLeft = 3;
        }
    }
    if(powerup == REDUCE_COOLDOWN){
        reduceCooldown = SPECIAL_COOLDOWN / 4;
    }
}

void SpaceShip::livesDecrease()
{
    if(shielded == false){
        livesLeft--;
    }
    else {
        shielded = false;
    }
}
