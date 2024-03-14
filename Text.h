#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "UsefulFunctions.h"

class Text
{
public:
	Text(SDL_Renderer* renderer);

	void DrawText(std::string text, int x, int y, int fontSize);

private:
	SDL_Renderer* renderer;
};

#endif // TEXT_H_INCLUDED
