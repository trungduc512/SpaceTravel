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

    enum PowerUpType { HEAL, SHIELD, REDUCE_COOLDOWN };

    bool shielded;
    bool died;
    unsigned int livesLeft;
    Uint32 lastShootTime;
    Uint32 lastSpecialShoot;
    int reduceCooldown;

    void Render(unsigned int frames);
    void RenderShield(unsigned int frames);
    void moveLeft();
    void moveRight();
	void moveUp();
	void moveDown();
	void PowerUp(int powerup);
	void livesDecrease();
	void SetPos(float x_pos, float y_pos);
	int RemainCooldown();
	int RemainCooldownSpecial();
	SDL_Rect* getLeftHitBox();
	SDL_Rect* getRightHitBox();
	SDL_Rect* getMainHitBox();
	bool isCollided(const SDL_Rect* rect);

private:
    SDL_Texture* shipTexture;
    SDL_Texture* flameTexture;
    SDL_Texture* shieldTexture;
    SDL_Rect renderBox;
    SDL_Rect renderBox2;
    SDL_Rect flame;
    SDL_Rect clipBox;
    SDL_Rect shieldClipBox;
    SDL_Rect mainHitbox;
	SDL_Rect leftHitbox;
	SDL_Rect rightHitbox;
};

#endif // SPACESHIP_H_INCLUDED
