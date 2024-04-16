#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "Button.h"
#include "Text.h"

class MainMenu : public Object
{
private:
	enum ButtonNames { NEW_GAME, LOAD_GAME, QUIT, RESET_HIGHSCORE, SOUND_ON, SOUND_OFF};
	SDL_Texture* texture;
	SDL_Rect renderRect;
	Text* text;

public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();
    Button* button[6];
    bool quitGame;
    bool play;
    bool resetHighscore;
    bool soundChange;
    bool soundOn;
    bool loadGame;

	void RenderMenu( Sint32 &bestScore);
	void HandleMenuEvent(SDL_Event &event);
	void CheckButton();
};

#endif // MAINMENU_H_INCLUDED
