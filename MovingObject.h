#ifndef MOVINGOBJECT_H_INCLUDED
#define MOVINGOBJECT_H_INCLUDED

#include "Object.h"
#include "GameConstants.h"

#include <time.h>
#include <stdlib.h>

class MovingObject : public Object
{
public:
	MovingObject(SDL_Renderer* renderer);
	MovingObject(SDL_Renderer* renderer, std::string path);
	MovingObject(SDL_Renderer* renderer, const SDL_Rect &mainHitBox);
	~MovingObject();

	SDL_Rect Box;

	float moveSpeed;

};

#endif // MOVINGOBJECT_H_INCLUDED
