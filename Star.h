#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include "MovingObject.h"

class Star : public MovingObject
{
public:
	Star(SDL_Renderer* renderer, int w, int h, float speed);
	~Star();

	void Update();
	void Render();
};

#endif // STAR_H_INCLUDED
