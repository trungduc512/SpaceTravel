#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "Object.h"
#include "GameConstants.h"
#include <string>

class SpaceShip : public Object
{
public:
    SpaceShip(SDL_Renderer* renderer, std::string path1, std::string path2);
    ~SpaceShip();

    bool shielded;
    bool died;

    void Render(unsigned int frames);
    void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void RenderShield();
	int RemainCooldown(Uint32 &lastShootTime);
	SDL_Rect* getLeftHitBox();
	SDL_Rect* getRightHitBox();
	SDL_Rect* getMainHitBox();
	bool isCollided(const SDL_Rect* rect);
	unsigned int coinEatToGetShield;
	void increaseCoinEatToGetShield();

private:
    SDL_Texture* shipTexture;
    SDL_Texture* flameTexture;
    SDL_Texture* shieldTexture;
    SDL_Rect renderBox;
    SDL_Rect renderBox2;
    SDL_Rect flame;
    SDL_Rect clipBox;
    SDL_Rect mainHitbox;
	SDL_Rect leftHitbox;
	SDL_Rect rightHitbox;
};

#endif // SPACESHIP_H_INCLUDED
