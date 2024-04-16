#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : Object(renderer)
{
    int pos = SCREEN_WIDTH / 2 - 300 / 2;
	button[NEW_GAME] = new Button(renderer, "image/New_game_button.png", pos, 400, 300, 50);
	button[RESET_HIGHSCORE] = new Button(renderer, "image/Reset_highscore_button.png", pos, 625, 300, 50);
	button[LOAD_GAME] = new Button(renderer, "image/Load_game_button.png", pos, 475, 300, 50);
	button[QUIT] = new Button(renderer, "image/Quit_button.png", pos, 700, 300, 50);
	button[SOUND_ON] = new Button(renderer, "image/SoundOn_button.png", pos, 550, 300, 50);
	button[SOUND_OFF] = new Button(renderer, "image/SoundOff_button.png", pos, 550, 300, 50);
	text = new Text(renderer);
    getTexture(texture,renderer,"image/MainMenu.png",69,69,69);
    play = false;
    quitGame = false;
    resetHighscore = false;
    soundChange = false;
    soundOn = true;
    loadGame = false;
    setRectSize(renderRect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}

MainMenu::~MainMenu()
{
    delete button[NEW_GAME];
	delete button[QUIT];
	delete button[RESET_HIGHSCORE];
	delete button[SOUND_ON];
	delete button[SOUND_OFF];
	delete button[LOAD_GAME];
	delete text;
}

void MainMenu::HandleMenuEvent(SDL_Event &event)
{
    for(int i = 0; i < 4; i++) {
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

void MainMenu::RenderMenu( Sint32 &bestScore )
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,&renderRect);
    for(int i = 0; i < 4; i++)
    {
        button[i]->render();
    }
    if(soundOn){
        button[SOUND_ON]->render();
    }
    else {
        button[SOUND_OFF]->render();
    }
    text->DrawText("Current best score: " + std::to_string(bestScore), 1300, 700, 30, -30.0);
    SDL_RenderPresent(renderer);
}

void MainMenu::CheckButton()
{
    if(button[NEW_GAME]->selected) {
        play = 1;
        button[NEW_GAME]->selected = false;
    }
    if(button[QUIT]->selected) {
        quitGame = 1;
        button[QUIT]->selected = false;
    }
    if(button[RESET_HIGHSCORE]->selected) {
        resetHighscore = 1;
        button[RESET_HIGHSCORE]->selected = false;
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
    if(button[LOAD_GAME]->selected) {
        loadGame = 1;
        button[LOAD_GAME]->selected = false;
    }
}
