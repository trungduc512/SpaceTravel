#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    Spaceship = NULL;
    energyBar = NULL;
    healthBar = NULL;
    explosion = NULL;
    text = NULL;
}

bool Game::Init()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    lastShootTime = 0;
    window = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) return false;
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL ) return false;
    return true;
}

void Game::NewGame()
{
    delete Spaceship;
    delete energyBar;
    delete explosion;
    delete healthBar;
	Spaceship = new SpaceShip(renderer,"image/spaceship.png", "image/engine_flame.png");
	text = new Text(renderer);
    energyBar = new HUD(renderer, "image/energy_bar.png");
    healthBar = new HUD(renderer, "image/health_bar.png");
    explosion = new Explosion(renderer);
	frame = 0;
	obstaclesSpawnRate = 25; // minimum rate is 1 per 3 frames
	coinSpawnRate = 100;
	starSpawnRate = 2;
	largeStarSpawnRate = 3;
	backgroundSpawnRate = 150;
	livesLeft = 3;
	score = 0;
	if(!obstaclesList.empty()){
        obstaclesList.erase(obstaclesList.begin(),obstaclesList.end());
	}
    if(!coinList.empty()){
        coinList.erase(coinList.begin(),coinList.end());
	}
    if(!bulletList.empty()){
        bulletList.erase(bulletList.begin(),bulletList.end());
	}
    if(!starList.empty()){
        starList.erase(starList.begin(),starList.end());
	}
    if(!largeStarList.empty()){
        largeStarList.erase(largeStarList.begin(),largeStarList.end());
	}
    if(!backgroundList.empty()){
        backgroundList.erase(backgroundList.begin(),backgroundList.end());
	}
}
void Game::Render()
{
    //set color for the window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //clear previous screen
    SDL_RenderClear(renderer);

    //iterate through star list
    for(Star* currentStar : starList){
        //render stars
        currentStar->Render();
    }

    for(Background* currentBackground : backgroundList){
        currentBackground->Render();
    }

    for(Star* currentStar : largeStarList){
        //render large stars
        currentStar->Render();
    }

    //render spaceship
    Spaceship->Render(frame);

    //iterate through bullet list
    if(!bulletList.empty()){
        std::list<Bullet*>::iterator currentBullet = bulletList.begin();
        while (currentBullet != bulletList.end()) {
            // Render bullet
            (*currentBullet)->Render();
            ++currentBullet;
        }
    }

    //iterate through obstacles list
    std::list<Obstacles*>::iterator currentObstacle = obstaclesList.begin();
    while (currentObstacle != obstaclesList.end()){
        //render asteroid
        (*currentObstacle)->Render();
        //check collision
        if(!bulletList.empty() && SDL_HasIntersection((*bulletList.begin())->getHitBox(),(*currentObstacle)->getHitBox())){
            //explode
            for(int i = 0; i < 4; i++){
                explosion->Render(i,(*currentObstacle)->getHitBox());
            }
                currentObstacle = obstaclesList.erase(currentObstacle);
                bulletList.erase(bulletList.begin());
                increaseScore(OBSTACLE_BREAK_POINT);
                continue;
        }
        if((*currentObstacle)->isCollided(Spaceship->getLeftHitBox(), Spaceship->getRightHitBox(), Spaceship->getMainHitBox())){
            //explode
            for(int i = 0; i < 4; i++){
                explosion->Render(i,(*currentObstacle)->getHitBox());
            }
            // erase returns the iterator following the last removed element
            currentObstacle = obstaclesList.erase(currentObstacle);
            livesLeft--;
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
            increaseScore(COIN_POINT);
        }
        else {
            ++currentCoin;
        }
    }
    energyBar->RenderEnergyBar(Spaceship->RemainCooldown(lastShootTime));
    healthBar->RenderHealthBar(livesLeft);
    text->DrawText("Score: ", 0, 0, 30);
    text->DrawText(std::to_string(score), 130, 0, 30);
    SDL_RenderPresent(renderer);
}

void Game::Run()
{
    NewGame();
    bool quit = false;
    while( quit == false )
    {
        frameStart = SDL_GetTicks();
        if( SDL_PollEvent( &event ) != 0)
        {
            if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE ) quit = true;
        }
        Update();
        Render();
        frame++;

        //stable fps
        frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}

        //debug
//        std::cout << frame << std::endl;
//        std::cout << obstaclesList.size() << std::endl;
//        std::cout << bulletList.size() << std::endl;
    }
    Quit();
}

void Game::Update()
{
    if(livesLeft == 0){
        SDL_Delay(1000);
        NewGame();
    }
    HandleInput();
    if(frame % obstaclesSpawnRate == 0){
        obstacle = new Obstacles(renderer);
		obstaclesList.push_back(obstacle);
    }

    if(frame % coinSpawnRate == 0){
        coin = new Coin(renderer, "image/coin.png");
		coinList.push_back(coin);
    }

    if(frame % largeStarSpawnRate == 0){
        largeStar = new Star(renderer, 5, 5, 7);
        largeStarList.push_back(largeStar);
    }

    if(frame % starSpawnRate == 0){
    	star = new Star(renderer, 1, 1, 5);
        starList.push_back(star);
    }

    if(frame % backgroundSpawnRate == 0){
    	background = new Background(renderer);
        backgroundList.push_back(background);
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
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        if( Spaceship->RemainCooldown(lastShootTime) == SHOOT_COOLDOWN ){
            bullet = new Bullet(renderer, Spaceship->getMainHitBox());
            bulletList.push_back(bullet);
            lastShootTime = SDL_GetTicks();
        }
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
    std::list<Star*>::iterator currentStar = starList.begin();
    while (currentStar != starList.end()){
        //Check if obstacle is off screen
        if ((*currentStar)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentStar);
            // erase returns the iterator following the last removed element
            currentStar = starList.erase(currentStar);
        }
        else {
            (*currentStar)->Update();
            ++currentStar;
        }
    }
    std::list<Star*>::iterator currentLargeStar = largeStarList.begin();
    while (currentLargeStar != largeStarList.end()){
        //Check if large star is off screen
        if ((*currentLargeStar)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentLargeStar);
            // erase returns the iterator following the last removed element
            currentLargeStar = largeStarList.erase(currentLargeStar);
        }
        else {
            (*currentLargeStar)->Update();
            ++currentLargeStar;
        }
    }
    std::list<Obstacles*>::iterator currentObstacle = obstaclesList.begin();
    while (currentObstacle != obstaclesList.end()){
        //Check if obstacle is off screen
        if ((*currentObstacle)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentObstacle);
            // erase returns the iterator following the last removed element
            currentObstacle = obstaclesList.erase(currentObstacle);
            //increase score by 1
            increaseScore(1);
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

    std::list<Bullet*>::iterator currentBullet = bulletList.begin();
    while (currentBullet != bulletList.end()) {
    // Check if bullet is off screen
        if ((*currentBullet)->Box.y < 0) {
            delete (*currentBullet);
            // erase returns the iterator following the last removed element
            currentBullet = bulletList.erase(currentBullet);
        }
        else {
            (*currentBullet)->Update();
            ++currentBullet;
        }
    }

    std::list<Background*>::iterator currentBackground = backgroundList.begin();
    while (currentBackground != backgroundList.end()) {
    // Check if background is off screen
        if ((*currentBackground)->Box.y > SCREEN_HEIGHT) {
            delete (*currentBackground);
            // erase returns the iterator following the last removed element
            currentBackground = backgroundList.erase(currentBackground);
        }
        else {
            (*currentBackground)->Update();
            ++currentBackground;
        }
    }
}

void Game::increaseScore(const int scoreGet)
{
    score += scoreGet;
}

void Game::Quit()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
    TTF_Quit();
}

