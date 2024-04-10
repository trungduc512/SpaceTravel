#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Object.h"

class Button : public Object
//The mouse button
{
	public:
		//Initializes internal variables
		Button(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h);
		Button(SDL_Renderer *renderer, float x, float y, float w, float h);
		~Button();

        bool selected;

		//Handles mouse event
		void handleEvent( SDL_Event* e );

		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Texture *texture;
		SDL_Rect renderRect;
};

#endif // BUTTON_H_INCLUDED
