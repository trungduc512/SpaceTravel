#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    Spaceship = NULL;
}

bool Game::Init()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) return false;
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL ) return false;
    return true;
}

void Game::NewGame()
{
	Spaceship = new SpaceShip(renderer,"image/spaceship.png", "image/engine_flame.png");
	frame = 0;
	obstaclesSpawnRate = 25; // minimum rate is 1 per 3 frames
	coinSpawnRate = 80;
	livesLeft = 3;
	if(!obstaclesList.empty()){
        obstaclesList.erase(obstaclesList.begin(),obstaclesList.end());
	}
    if(!coinList.empty()){
        coinList.erase(coinList.begin(),coinList.end());
	}
}
void Game::Render()
{
    //set color for the window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    //iterate through obstacles list
    std::list<Obstacles*>::iterator currentObstacle = obstaclesList.begin();
    while (currentObstacle != obstaclesList.end()){
        //render asteroid
        (*currentObstacle)->Render();
        //check collision
        if((*currentObstacle)->isCollided(Spaceship->getLeftHitBox(), Spaceship->getRightHitBox(), Spaceship->getMainHitBox())){
            // erase returns the iterator following the last removed element
            currentObstacle = obstaclesList.erase(currentObstacle);
//            livesLeft--;
        }
        else {
            ++currentObstacle;
        }
    }

    //iterate through coin list
    std::list<Coin*>::iterator currentCoin = coinList.begin();
    while (currentCoin != coinList.end()){
        //render asteroid
        (*currentCoin)->Render(frame);
        //check collision
        if((*currentCoin)->isCollided(Spaceship->getLeftHitBox(), Spaceship->getRightHitBox(), Spaceship->getMainHitBox())){
            // erase returns the iterator following the last removed element
            currentCoin = coinList.erase(currentCoin);
        }
        else {
            ++currentCoin;
        }
    }
    Spaceship->Render(frame);
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
        std::cout << obstaclesList.size() << std::endl;
    }
    delete Spaceship;
    Quit();
}

void Game::Update()
{
    HandleInput();
    if(livesLeft == 0){
        SDL_Delay(1000);
        NewGame();
    }
    if(frame % obstaclesSpawnRate == 0){
        obstacle = new Obstacles(renderer);
		obstaclesList.push_back(obstacle);
    }

    if(frame % coinSpawnRate == 0){
        coin = new Coin(renderer, "image/coin.png");
		coinList.push_back(coin);
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

void Game::KeepInScreen(Object* object)
{
    if(object->x < 0) object->x = 0;
    if(object->x + object->width > SCREEN_WIDTH) object->x = SCREEN_WIDTH - object->width;
    if(object->y < 0) object->y = 0;
    if(object->y + object->height > SCREEN_HEIGHT) object->y = SCREEN_HEIGHT - object->height;
}

void Game::IterateThroughList()
{
    std::list<Obstacles*>::iterator currentObstacle = obstaclesList.begin();
    while (currentObstacle != obstaclesList.end()){
        //Check if obstacle is off screen
        if ((*currentObstacle)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentObstacle);
            // erase returns the iterator following the last removed element
            currentObstacle = obstaclesList.erase(currentObstacle);
        }
        else {
            (*currentObstacle)->Update();
            ++currentObstacle;
        }
    }
    std::list<Coin*>::iterator currentCoin = coinList.begin();
    while (currentCoin != coinList.end()){
        //Check if coin is off screen
        if ((*currentCoin)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentCoin);
            // erase returns the iterator following the last removed element
            currentCoin = coinList.erase(currentCoin);
        }
        else {
            (*currentCoin)->Update();
            ++currentCoin;
        }
    }
}

void Game::Quit()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
}

