#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include "MovingObject.h"

class Star : public MovingObject
{
public:
	Star(SDL_Renderer* renderer, int w, int h, float speed);
	Star(SDL_Renderer* renderer, int typeOfStar, float x, float y);
	~Star();

	void Update();
	void Render();
	void SetPos(float x_pos, float y_pos);
};

#endif // STAR_H_INCLUDED
