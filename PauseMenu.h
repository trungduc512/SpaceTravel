#ifndef PAUSEMENU_H_INCLUDED
#define PAUSEMENU_H_INCLUDED

#include "Button.h"

class PauseMenu : public Object
{
private:
	enum ButtonNames { RESUME, SAVE, QUIT, SOUND_ON, SOUND_OFF };
	SDL_Texture* texture;
	SDL_Rect renderRect;

public:
	PauseMenu(SDL_Renderer* renderer);
	~PauseMenu();
    Button* button[5];
    bool quitGame;
    bool resume;
    bool soundChange;
    bool soundOn;
    bool saveGame;

	void RenderMenu();
	void HandleMenuEvent(SDL_Event &event);
	void CheckButton();
	void GetSoundState(bool soundState);
};

#endif // PAUSEMENU_H_INCLUDED
