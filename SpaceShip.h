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

private:
    SDL_Rect mainColliderRect;
	SDL_Rect leftColliderRect;
	SDL_Rect rightColliderRect;
};

#endif // SPACESHIP_H_INCLUDED
