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
#include "Timer.h"
#include "GameOverMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Boss.h"
#include <SDL.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

class Game
{
public:
    Game();

//    enum SPACESHIP_STATS { POSITION, LIVESLEFT, SHIELDED }; //3
//    enum OBSTACLE_TYPE { ASTEROID1, ASTEROID2, ASTEROID3, SATELLITE, UFO, AMOGUS }; //6
//    enum COIN_TYPE { NORMAL_COIN, HEART, BATTERY, SHIELD }; //4
//    enum BACKGROUND_TYPE { EARTH, GALAXY1, GALAXY2, GALAXY3, PLANET1, PLANET2, MARS, BLACKHOLE }; //8

    bool Init();
    void InitNullValues();
    void Render();
    void RenderObjects();
    void RenderLaser();
    void RenderText();
    void RenderHUD();
    void RenderBoss();
    void RenderSpaceship();
    void RenderSpaceshipBullet();
    void RenderWarning();
    void RenderBackground();
    void RenderObstacles();
    void RenderCoin();
    void LaserHandle();
    void CheckBulletAndObstaclesCollision();
    void CheckDeath();
    void CreateMenus();
    void InitBestScore();
    void CreateComplicateTexture();
    void NewGame();
    void PlayLoadGame();
    void SaveGame();
    void LoadGame();
    void ClearGameObjects();
    void ClearLists();
    void NewGameObjects();
    void NewMusic();
    void InitNewGameStats();
    void StartTimers();
    void Run();
    void Update();
    void UpdateBoss();
    void UpdateList();
    void KeepInScreen(Object* object);
    void HandleInput();
    void HandleMusicVolume();
    void SpawnObjects();
    template <typename Container> void UpdateList(std::list<Container> &checklist);
    template <typename Container> void ClearList(std::list<Container> &checklist);
    void increaseScore(int scoreGet);
    void RenderGameOverScreen();
    void GameOver();
    void EnterMainMenu();
    void Pause();
    void StartGame();
    void Quit();
    void GameLoop();
    bool NewLaser();
    bool NewBoss();
    void PauseHandle();
    void updateLevel();
    void freePointers();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    Mix_Music* music;
    SDL_GameController* gameController;
    SpaceShip* Spaceship;
    Menu* quitMenu;
    MainMenu* mainMenu;
    PauseMenu* pauseMenu;
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
    Boss* boss;
    Background* background;
    unsigned int frame;
    unsigned int obstaclesSpawnRate;
    unsigned int coinSpawnRate;
    unsigned int largeStarSpawnRate;
    unsigned int starSpawnRate;
    unsigned int backgroundSpawnRate;
    unsigned int volume;
    unsigned int level;
    unsigned int coinCounted;
    float obstacleMoveSpeed;
    Uint32 lastShootTime;
    Uint32 lastSpecialShoot;
    Uint32 frameStart;
	Uint32 frameTime;
	Sint32 bestScore;
    Sint32 score;
	SDL_RWops* file;
	Timer timer;
	Timer laserTimer;
	Timer bossTimer;
	SDL_Texture* warningTexture;
	SDL_Texture* laserTexture;
	SDL_Texture* bossTexture;
	SDL_Texture* specialBulletTexture;
	SDL_Rect laserHitbox;
	bool isPause;
	bool laserOn;
	bool laserContact;
	bool hasBoss;
	bool quit;
	bool soundOn;
	bool levelUpdate1;
	bool levelUpdate2;
	bool newgame;
	int pos;
	int lastIncreaseSpeed;
};

#endif // GAME_H_INCLUDED
