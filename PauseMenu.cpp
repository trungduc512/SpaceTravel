#include "PauseMenu.h"

PauseMenu::PauseMenu(SDL_Renderer* renderer) : Object(renderer)
{
    int pos = SCREEN_WIDTH / 2 - 300 / 2;
	button[RESUME] = new Button(renderer, "image/Resume_button.png", pos, 400, 300, 50); //75px apart
	button[QUIT] = new Button(renderer, "image/Quit_button.png", pos, 625, 300, 50);
	button[SAVE] = new Button(renderer, "image/Save_game_button.png", pos, 475, 300, 50);
	button[SOUND_ON] = new Button(renderer, "image/SoundOn_button.png", pos, 550, 300, 50);
	button[SOUND_OFF] = new Button(renderer, "image/SoundOff_button.png", pos, 550, 300, 50);
    getTexture(texture,renderer,"image/MainMenu.png",69,69,69);
    quitGame = false;
    resume = false;
    soundChange = false;
    saveGame = false;
    setRectSize(renderRect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}

PauseMenu::~PauseMenu()
{
    delete button[RESUME];
	delete button[QUIT];
	delete button[SOUND_ON];
	delete button[SOUND_OFF];
	delete button[SAVE];
}

void PauseMenu::HandleMenuEvent(SDL_Event &event)
{
    for(int i = 0; i < 3; i++) {
        button[i]->handleEvent(&event);
    }
    if(soundOn){
        button[SOUND_ON]->handleEvent(&event);
    }
    else{
        button[SOUND_OFF]->handleEvent(&event);
    }
    CheckButton();
}

void PauseMenu::RenderMenu()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,&renderRect);
    for(int i = 0; i < 3; i++)
    {
        button[i]->render();
    }
    if(soundOn){
        button[SOUND_ON]->render();
    }
    else {
        button[SOUND_OFF]->render();
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
    if(button[SAVE]->selected) {
        saveGame = 1;
        button[SAVE]->selected = false;
    }
    if(button[SOUND_ON]->selected) {
        soundChange = true;
        soundOn = !soundOn;
        button[SOUND_ON]->selected = false;
    }
    if(button[SOUND_OFF]->selected) {
        soundChange = true;
        soundOn = !soundOn;
        button[SOUND_OFF]->selected = false;
    }

}

void PauseMenu::GetSoundState(bool soundState)
{
    soundOn = soundState;
}
