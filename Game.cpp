#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    Spaceship = NULL;
}

bool Game::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) return false;
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL ) return false;
    return true;
}

void Game::NewGame()
{
	Spaceship = new SpaceShip(renderer,"image/spaceship.png");
	frame = 0;
	asteroidSpawnRate = 25;
	livesLeft = 3;
	if(!asteroidList.empty()){
        asteroidList.erase(asteroidList.begin(),asteroidList.end());
	}
}
void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    Spaceship->Render();
    std::list<Asteroid*>::iterator currentAsteroid = asteroidList.begin();
    while (currentAsteroid != asteroidList.end()){
        //render asteroid
        (*currentAsteroid)->Render();
        //check collision
        if((*currentAsteroid)->isCollided(Spaceship->getLeftHitBox(), Spaceship->getRightHitBox(), Spaceship->getMainHitBox())){
            // erase returns the iterator following the last removed element
            currentAsteroid = asteroidList.erase(currentAsteroid);
        }
        else {
            ++currentAsteroid;
        }
    }

    if(livesLeft == 0){
        NewGame();
    }
    SDL_RenderPresent(renderer);
}

void Game::Run()
{
    NewGame();
    bool quit = false;
    while( quit == false )
    {
        if( SDL_PollEvent( &event ) != 0)
        {
            if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE ) quit = true;

        }
        Update();
        Render();
        frame++;
        //debug
        std::cout << frame << std::endl;
        std::cout << asteroidList.size() << std::endl;
    }
    delete Spaceship;
    Quit();
}

void Game::Update()
{
    HandleInput();
    if(frame % asteroidSpawnRate == 0){
        asteroid = new Asteroid(renderer);
		asteroidList.push_back(asteroid);
    }
    KeepInScreen(Spaceship);
    IterateThroughList();
}
void Game::HandleInput()
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
	if (currentKeyState[SDL_SCANCODE_A] || currentKeyState[SDL_SCANCODE_LEFT])
	{
		Spaceship->moveLeft();
	}
	if (currentKeyState[SDL_SCANCODE_D] || currentKeyState[SDL_SCANCODE_RIGHT])
	{
		Spaceship->moveRight();
	}
	if (currentKeyState[SDL_SCANCODE_W] || currentKeyState[SDL_SCANCODE_UP])
	{
		Spaceship->moveUp();
	}
	if (currentKeyState[SDL_SCANCODE_S] || currentKeyState[SDL_SCANCODE_DOWN])
	{
		Spaceship->moveDown();
	}
}

void Game::KeepInScreen(SpaceShip *Spaceship)
{
    if(Spaceship->x < 0) Spaceship->x = 0;
    if(Spaceship->x + Spaceship->width > SCREEN_WIDTH) Spaceship->x = SCREEN_WIDTH - Spaceship->width;
    if(Spaceship->y < 0) Spaceship->y = 0;
    if(Spaceship->y + Spaceship->height > SCREEN_HEIGHT) Spaceship->y = SCREEN_HEIGHT - Spaceship->height;
}

void Game::IterateThroughList()
{
    std::list<Asteroid*>::iterator currentAsteroid = asteroidList.begin();
    while (currentAsteroid != asteroidList.end()){
        //Check if asteroid is off screen
        if ((*currentAsteroid)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentAsteroid);
            // erase returns the iterator following the last removed element
            currentAsteroid = asteroidList.erase(currentAsteroid);
        }
        else {
            (*currentAsteroid)->Update();
            ++currentAsteroid;
        }
    }
}

void Game::Quit()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
}

