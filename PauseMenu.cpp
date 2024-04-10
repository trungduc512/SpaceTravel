#include "PauseMenu.h"

PauseMenu::PauseMenu(SDL_Renderer* renderer) : Object(renderer)
{
    int pos = SCREEN_WIDTH / 2 - 300 / 2;
	button[RESUME] = new Button(renderer, "image/Resume_button.png", pos, 400, 300, 50);
	button[QUIT] = new Button(renderer, "image/Quit_button.png", pos, 550, 300, 50);
	button[SOUNDON] = new Button(renderer, "image/SoundOn_button.png", pos, 475, 300, 50);
	button[SOUNDOFF] = new Button(renderer, "image/SoundOff_button.png", pos, 475, 300, 50);
    getTexture(texture,renderer,"image/MainMenu.png",69,69,69);
    quitGame = false;
    resume = false;
    soundChange = false;
    setRectSize(renderRect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}

PauseMenu::~PauseMenu()
{
    delete button[RESUME];
	delete button[QUIT];
	delete button[SOUNDON];
	delete button[SOUNDOFF];
}

void PauseMenu::HandleMenuEvent(SDL_Event &event)
{
    for(int i = 0; i < 2; i++) {
        button[i]->handleEvent(&event);
    }
    if(soundOn){
        button[SOUNDON]->handleEvent(&event);
    }
    else{
        button[SOUNDOFF]->handleEvent(&event);
    }
    CheckButton();
}

void PauseMenu::RenderMenu()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,&renderRect);
    for(int i = 0; i < 2; i++)
    {
        button[i]->render();
    }
    if(soundOn){
        button[SOUNDON]->render();
    }
    else {
        button[SOUNDOFF]->render();
    }
    SDL_RenderPresent(renderer);
}

void PauseMenu::CheckButton()
{
    if(button[RESUME]->selected) {
        resume = 1;
        button[RESUME]->selected = false;
    }
    if(button[QUIT]->selected) {
        quitGame = 1;
        button[QUIT]->selected = false;
    }
    if(button[SOUNDON]->selected) {
        soundChange = true;
        soundOn = !soundOn;
        button[SOUNDON]->selected = false;
    }
    if(button[SOUNDOFF]->selected) {
        soundChange = true;
        soundOn = !soundOn;
        button[SOUNDOFF]->selected = false;
    }
}

void PauseMenu::GetSoundState(bool soundState)
{
    soundOn = soundState;
}
