#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameConstants.h"
#include "SpaceShip.h"
#include "Obstacles.h"
#include "Coin.h"
#include "Bullet.h"
#include "Text.h"
#include <SDL.h>
#include <iostream>
#include <list>
#include <string>
#include <sstream>

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
    void increaseScore(int n);
    void Quit();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    SpaceShip* Spaceship;
    std::list<Obstacles*> obstaclesList;
    std::list<Coin*> coinList;
    std::list<Bullet*> bulletList;
    Obstacles* obstacle;
    Coin* coin;
    Bullet* bullet;
    Text* text;
    unsigned int frame;
    unsigned int obstaclesSpawnRate;
    unsigned int coinSpawnRate;
    unsigned int livesLeft;
    unsigned int score;
    bool newGameFlag;
    Uint32 lastShootTime;
    Uint32 frameStart;
	Uint32 frameTime;
};

#endif // GAME_H_INCLUDED
