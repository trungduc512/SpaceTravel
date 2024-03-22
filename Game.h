#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameConstants.h"
#include "SpaceShip.h"
#include "Obstacles.h"
#include "Coin.h"
#include "Bullet.h"
#include "Text.h"
#include "HUD.h"
#include "Explosion.h"
#include "Star.h"
#include "Background.h"
#include "Audio.h"
#include <SDL.h>
#include <iostream>
#include <list>
#include <string>

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
    void UpdateList();
    void increaseScore(int scoreGet);
    void Quit();
    void PauseHandle();
    void updateLevel();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    Mix_Music* music;
    SpaceShip* Spaceship;
    HUD* energyBar;
    HUD* healthBar;
    Explosion* explosion;
    Audio* audio;
    std::list<Obstacles*> obstaclesList;
    std::list<Background*> backgroundList;
    std::list<Coin*> coinList;
    std::list<Bullet*> bulletList;
    std::list<Star*> starList;
    std::list<Star*> largeStarList;
    Obstacles* obstacle;
    Coin* coin;
    Bullet* bullet;
    Text* text;
    Star* star;
    Star* largeStar;
    Background* background;
    unsigned int frame;
    unsigned int obstaclesSpawnRate;
    unsigned int coinSpawnRate;
    unsigned int largeStarSpawnRate;
    unsigned int starSpawnRate;
    unsigned int backgroundSpawnRate;
    unsigned int livesLeft;
    float obstacleMoveSpeed;
    Uint32 lastShootTime;
    Uint32 frameStart;
	Uint32 frameTime;
	Sint32 bestScore;
    Sint32 score;
	SDL_RWops* file;
	bool isPause;
};

#endif // GAME_H_INCLUDED
