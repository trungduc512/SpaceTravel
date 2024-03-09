#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "Object.h"
#include "GameConstants.h"

class SpaceShip : public Object
{
public:
    SpaceShip(SDL_Renderer* renderer);
    ~SpaceShip();

    void Render();
    void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	SDL_Rect* getLeftHitBox();
	SDL_Rect* getRightHitBox();
	SDL_Rect* getMainHitBox();

private:
    SDL_Rect mainHitbox;
	SDL_Rect leftHitbox;
	SDL_Rect rightHitbox;
};

#endif // SPACESHIP_H_INCLUDED
