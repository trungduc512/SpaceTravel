#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameConstants.h"
#include <SDL.h>

class Game
{
public:
    Game();
    bool Init();
    void Run();
    void Quit();
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
};

#endif // GAME_H_INCLUDED
