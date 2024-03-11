#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameConstants.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include <SDL.h>
#include <iostream>
#include <list>

class Game
{
public:
    Game();
    bool Init();
    void Render();
    void NewGame();
    void Run();
    void Update();
    void HandleInput();
    void KeepInScreen(Object* object);
    void IterateThroughList();
    void Quit();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    SpaceShip* Spaceship;
    std::list<Asteroid*> asteroidList;
    Asteroid* asteroid;
    unsigned int frame;
    unsigned int asteroidSpawnRate;
    unsigned int livesLeft;
};

#endif // GAME_H_INCLUDED
