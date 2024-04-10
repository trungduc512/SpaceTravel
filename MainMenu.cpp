#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : Object(renderer)
{
    int pos = SCREEN_WIDTH / 2 - 300 / 2;
	button[PLAY] = new Button(renderer, "image/Play_button.png", pos, 400, 300, 50);
	button[RESET_HIGHSCORE] = new Button(renderer, "image/Reset_highscore_button.png", pos, 550, 300, 50);
	button[QUIT] = new Button(renderer, "image/Quit_button.png", pos, 625, 300, 50);
	button[SOUNDON] = new Button(renderer, "image/SoundOn_button.png", pos, 475, 300, 50);
	button[SOUNDOFF] = new Button(renderer, "image/SoundOff_button.png", pos, 475, 300, 50);
	text = new Text(renderer);
    getTexture(texture,renderer,"image/MainMenu.png",69,69,69);
    play = false;
    quitGame = false;
    resetHighscore = false;
    soundChange = false;
    soundOn = true;
    setRectSize(renderRect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}

MainMenu::~MainMenu()
{
    delete button[PLAY];
	delete button[QUIT];
	delete button[RESET_HIGHSCORE];
	delete button[SOUNDON];
	delete button[SOUNDOFF];
	delete text;
}

void MainMenu::HandleMenuEvent(SDL_Event &event)
{
    for(int i = 0; i < 3; i++) {
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

void MainMenu::RenderMenu( Sint32 &bestScore )
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,&renderRect);
    for(int i = 0; i < 3; i++)
    {
        button[i]->render();
    }
    if(soundOn){
        button[SOUNDON]->render();
    }
    else {
        button[SOUNDOFF]->render();
    }
    text->DrawText("Current best score: " + std::to_string(bestScore), 1300, 700, 30, -30.0);
    SDL_RenderPresent(renderer);
}

void MainMenu::CheckButton()
{
    if(button[PLAY]->selected) {
        play = 1;
        button[PLAY]->selected = false;
    }
    if(button[QUIT]->selected) {
        quitGame = 1;
        button[QUIT]->selected = false;
    }
    if(button[RESET_HIGHSCORE]->selected) {
        resetHighscore = 1;
        button[RESET_HIGHSCORE]->selected = false;
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
