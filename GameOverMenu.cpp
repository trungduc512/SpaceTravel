#include "GameOverMenu.h"

Menu::Menu(SDL_Renderer* renderer) : Object(renderer)
{
	button[PLAY] = new Button(renderer, "image/Yes_button.png", 700, 650, 200, 100);
	button[QUIT] = new Button(renderer, "image/No_button.png", 980, 650, 200, 100);
	getTexture(megamanTexture, renderer, "image/megaman.png", 69, 69, 69);
	getTexture(texture,renderer,"image/gameover_bg.png",69,69,69);
    playAgain = false;
    quitGame = false;
    setRectSize(renderRect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    setRectSize(renderRect2,825,240,100,100);
}

Menu::~Menu()
{
    delete button[PLAY];
	delete button[QUIT];
}

void Menu::HandleMenuEvent(SDL_Event &event)
{
    for(int i = 0; i < 2; i++) {
        button[i]->handleEvent(&event);
    }
    CheckButton();
}

void Menu::RenderMenu( unsigned int frame )
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,&renderRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i < 2; i++)
    {
        button[i]->render();
    }

    setRectSize(clipRect,400 * ((frame / 15) % 3), 0, 400, 360);
    SDL_RenderCopy(renderer,megamanTexture,&clipRect,&renderRect2);

    SDL_RenderPresent(renderer);
}

void Menu::CheckButton()
{
    if(button[PLAY]->selected) {
        playAgain = 1;
        button[PLAY]->selected = false;
    }
    if(button[QUIT]->selected) {
        quitGame = 1;
        button[QUIT]->selected = false;
    }
}
