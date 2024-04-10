#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Button.h"

class Menu : public Object
{
private:
	enum ButtonNames { PLAY, QUIT };
    SDL_Texture* texture;
    SDL_Texture* megamanTexture;
    SDL_Rect renderRect;
    SDL_Rect renderRect2;
    SDL_Rect clipRect;

public:
	Menu(SDL_Renderer* renderer);
	~Menu();
    Button* button[2];
    bool quitGame;
    bool playAgain;

	void RenderMenu(unsigned int frame);
	void HandleMenuEvent(SDL_Event &event);
	void CheckButton();
};

#endif // MENU_H_INCLUDED
