#include "Button.h"

Button::Button(SDL_Renderer* renderer, std::string path, float x, float y, float w, float h) : Object(renderer)
{
    getTexture(texture, renderer, path, 0, 0, 0);
    this->x = x;
    this->y = y;
    width = w;
    height = h;
    setRectSize(renderRect, x, y, width, height);
	selected = 0;
}

Button::~Button()
{
    SDL_DestroyTexture(texture);
}

void Button::handleEvent( SDL_Event* event )
{
	//If mouse event happened
	if( event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int mouseX, mouseY;
		SDL_GetMouseState( &mouseX, &mouseY );
		mouseX *= MOUSE_X_CONVERT_RATE;
		mouseY *= MOUSE_Y_CONVERT_RATE;

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( mouseX < this->x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( mouseX > this->x + width )
		{
			inside = false;
		}
		//Mouse above the button
		else if( mouseY < this->y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( mouseY > this->y + height )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
		    //render smaller button
		    setRectSize(renderRect, x, y, width, height);
		}
		//Mouse is inside button
		else
		{
		    //render bigger button
            setRectSize(renderRect, x - width * 0.05, y - height * 0.05, width * 1.1, height * 1.1);

			//Set mouse over sprite
			switch( event->type )
			{
                case SDL_MOUSEMOTION:
                break;

				case SDL_MOUSEBUTTONDOWN:
                //do stuff
                setRectSize(renderRect, x, y, width, height);
				break;

				case SDL_MOUSEBUTTONUP:
                //do stuff
                selected = true;
				break;
			}
		}
	}
}

void Button::render()
{
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderDrawRect(renderer, &renderRect);
}
