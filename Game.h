#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameConstants.h"
#include "SpaceShip.h"
#include <SDL.h>

class Game
{
public:
    Game();
    bool Init();
    void Render();
    void NewGame();
    void Run();
    void HandleInput();
    void KeepInScreen(SpaceShip *Spaceship);
    void Quit();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    SpaceShip* Spaceship;
};

#endif // GAME_H_INCLUDED
