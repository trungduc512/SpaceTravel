#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "Button.h"
#include "Text.h"

class MainMenu : public Object
{
private:
	enum ButtonNames { PLAY, QUIT, RESET_HIGHSCORE, SOUNDON, SOUNDOFF};
	SDL_Texture* texture;
	SDL_Rect renderRect;
	Text* text;

public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();
    Button* button[5];
    bool quitGame;
    bool play;
    bool resetHighscore;
    bool soundChange;
    bool soundOn;

	void RenderMenu( Sint32 &bestScore);
	void HandleMenuEvent(SDL_Event &event);
	void CheckButton();
};

#endif // MAINMENU_H_INCLUDED
