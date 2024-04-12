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
    music = NULL;
    audio = NULL;
    boss = NULL;
}

bool Game::Init()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    window = SDL_CreateWindow( "SpaceTravel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if( window == NULL ) return false;
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL ) return false;
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    file = SDL_RWFromFile( "bestscore.bin", "r+b" );
    if(file == NULL) {
        // create new file
        file = SDL_RWFromFile( "bestscore.bin", "w+b" );
        //initialize data
        bestScore = 0;
    }
    else {
        SDL_RWread( file, &bestScore, sizeof(Sint32), 1 );
    }
    //close file handler
    SDL_RWclose( file );
    //init menu
    mainMenu = new MainMenu(renderer);
    quitMenu = new Menu(renderer);
    quit = false;
    soundOn = true;
    pauseMenu = new PauseMenu(renderer);
    getTexture(specialBulletTexture, renderer, "image/enhance_canon.png", 61, 61, 61);
    getTexture(bossTexture, renderer, "image/monster_sprite_sheet.png", 69, 69, 69);
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
    getTexture(warningTexture, renderer, "image/warning.png", 69, 69, 69);
    getTexture(laserTexture, renderer, "image/laser.png", 0, 0, 0);
    if(soundOn){
        Mix_VolumeMusic(20);
    }
    music = Mix_LoadMUS("sound/spacemusic.wav");
    Mix_PlayingMusic();
    Mix_PlayMusic(music, -1);
	frame = 0;
	obstaclesSpawnRate = INIT_OBSTACLE_SPAWN_RATE;// minimum rate is 1 per 3 frames
	obstacleMoveSpeed = INIT_OBSTACLE_MOVE_SPEED;
	Spaceship->died = false;
	quitMenu->quitGame = 0;
	quitMenu->playAgain = 0;
	coinSpawnRate = COIN_SPAWN_RATE;
	starSpawnRate = STAR_SPAWN_RATE;
	largeStarSpawnRate = LARGE_STAR_SPAWN_RATE;
	backgroundSpawnRate = BACKGROUND_SPAWN_RATE;
	Spaceship->livesLeft = 3;
	score = 0;
	isPause = 0;
	Spaceship->lastShootTime = 0;
	Spaceship->lastSpecialShoot = 0;
	pos = 0;
	laserOn = 0;
	laserContact = 0;
	hasBoss = 0;
	level = 1;
	levelUpdate1 = 0;
	levelUpdate2 = 0;
	coinCounted = 0;
	lastIncreaseSpeed = 0;
	timer.start();
	bossTimer.start();

    ClearList<Obstacles*>(obstaclesList);
    ClearList<Bullet*>(bulletList);
    ClearList<Star*>(starList);
    ClearList<Star*>(largeStarList);
    ClearList<Background*>(backgroundList);
    ClearList<Coin*>(coinList);
}

void Game::Run()
{
    //render main menu
    while(mainMenu->play == false && quit == false){
        if( SDL_PollEvent( &event ) != 0)
        {
            if( event.type == SDL_QUIT ) quit = true;
        }
        StartGame();
    }

    //start new game
    NewGame();

    //gameloop
    while( quit == false )
    {
        frameStart = SDL_GetTicks();
        if( SDL_PollEvent( &event ) != 0)
        {
            if( event.type == SDL_QUIT ) quit = true;
        }

        //check if the game is paused
        PauseHandle();
        //update and render
        if(!isPause){
            if(Spaceship->died == false){
                Update();
                Render();
                frame++;
            }
            else {
                GameOver();
                frame++;
            }
        }

        else {
            Pause();
        }
        if(soundOn){
            Mix_VolumeMusic(20);
        }
        else{
            Mix_VolumeMusic(0);
        }
        //std::cout << obstacleMoveSpeed << std::endl;
        //stable fps
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
    Quit();
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

    if(Spaceship->shielded == true){
        Spaceship->RenderShield();
    }
    //render laser
    if(NewLaser() || laserOn){
        if(laserTimer.getTicks() == 0) {
            audio->playSound("sound/LaserSound1.wav",soundOn);
        }
        if(laserTimer.getTicks() <= WARNING_TIME) {
            RenderWarning();
        }

        else {
            RenderLaser();
            //debug
            //SDL_SetRenderDrawColor(renderer, 226, 33, 33, 255);
            //SDL_RenderDrawRect(renderer, &laserHitbox);
            if(Spaceship->isCollided(&laserHitbox) && laserContact == 0){
                audio->playSound("sound/LaserSoundHit.wav",soundOn);
                laserContact = 1;
                Spaceship->livesDecrease();
            }
        }

        if(laserTimer.getTicks() > WARNING_TIME + LASER_DURATION){
            laserOn = 0;
            laserContact = 0;
            laserTimer.stop();
        }
    }

    //iterate through bullet list
    if(!bulletList.empty()){
        std::list<Bullet*>::iterator currentBullet = bulletList.begin();
        while (currentBullet != bulletList.end()) {
            // Render bullet
            if((*currentBullet)->isSpecialBullet)
                (*currentBullet)->Render(frame);
            else
                (*currentBullet)->Render();
            ++currentBullet;
        }
    }



    //check bullet collision with obstacles
    if(!bulletList.empty()){
        std::list<Bullet*>::iterator currentBullet = bulletList.begin();
        while (currentBullet != bulletList.end()) {
            bool checkBulletCollision = 0;
            std::list<Obstacles*>::iterator currentObstacle = obstaclesList.begin();
            while(currentObstacle != obstaclesList.end()){
                if(SDL_HasIntersection((*currentBullet)->getHitBox(),(*currentObstacle)->getHitBox())){
                    //explode
                    if(!(*currentBullet)->isSpecialBullet){
                        currentBullet = bulletList.erase(currentBullet);
                    }
                    for(int i = 0; i < 4; i++){
                        explosion->Render(i,(*currentObstacle)->getHitBox());
                    }
                    currentObstacle = obstaclesList.erase(currentObstacle);
                    checkBulletCollision = 1;
                    increaseScore(OBSTACLE_BREAK_POINT);
                    audio->playSound("sound/AsteroidHit.wav",soundOn);
                    break;
                }
                else{
                    ++currentObstacle;
                }
            }
            if(!checkBulletCollision)
                ++currentBullet;
        }
    }

    //iterate through obstacles list
    std::list<Obstacles*>::iterator currentObstacle = obstaclesList.begin();
    while (currentObstacle != obstaclesList.end()){
        //render obstacles
        (*currentObstacle)->Render();
        //check spaceship collision
        if(Spaceship->isCollided((*currentObstacle)->getHitBox())){
            //explode
            for(int i = 0; i < 4; i++){
                explosion->Render(i,(*currentObstacle)->getHitBox());
            }
            // erase returns the iterator following the last removed element
            currentObstacle = obstaclesList.erase(currentObstacle);
            audio->playSound("sound/crash.wav",soundOn);
            Spaceship->livesDecrease();
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
        if(Spaceship->isCollided((*currentCoin)->getHitBox())){
            // erase returns the iterator following the last removed element
            Spaceship->PowerUp((*currentCoin)->powerUpType);
            if((*currentCoin)->powerUpType == -1)
                audio->playSound("sound/CoinEaten.wav",soundOn);
            else
                audio->playSound("sound/get_power_up.wav",soundOn);
            increaseScore(COIN_POINT);
            currentCoin = coinList.erase(currentCoin);
        }
        else {
            ++currentCoin;
        }
    }
    if(NewBoss() || hasBoss){
        boss->Render(frame);//test
        if(!bulletList.empty()){
            std::list<Bullet*>::iterator currentBullet = bulletList.begin();
            while (currentBullet != bulletList.end()) {
                if(SDL_HasIntersection(boss->getHitBox(),(*currentBullet)->getHitBox())){
                    if(!(*currentBullet)->isSpecialBullet)
                        boss->DecreaseLives(BULLET_DAMAGE);
                    else
                        boss->DecreaseLives(SPECIAL_BULLET_DAMAGE);
                    currentBullet = bulletList.erase(currentBullet);
                    continue;
                }
                else{
                    ++currentBullet;
                }
            }
        }
        if(boss->getHitBox()->y + boss->getHitBox()->w < 0 && !boss->alive){
            hasBoss = 0;
            increaseScore(BOSS_DEFEAT_POINT);
            bossTimer.start();
        }
        if(!boss->bossBulletList.empty()){
            std::list<Bullet*>::iterator currentBullet = boss->bossBulletList.begin();
            while (currentBullet != boss->bossBulletList.end()) {
                if(Spaceship->isCollided((*currentBullet)->getHitBox())){
                    Spaceship->livesDecrease();
                    currentBullet = boss->bossBulletList.erase(currentBullet);
                }
                else{
                    ++currentBullet;
                }
            }
        }
    }

    energyBar->RenderEnergyBar(Spaceship->RemainCooldownSpecial()); // last special shoot
    healthBar->RenderHealthBar(Spaceship->livesLeft);
    text->DrawText("Score: ", SCORE_BOARD_X_POS, SCORE_BOARD_Y_POS, 30);
    text->DrawText(std::to_string(score), SCORE_BOARD_X_POS + 130, SCORE_BOARD_Y_POS, 30);
    text->DrawText("Best: ", SCORE_BOARD_X_POS, SCORE_BOARD_Y_POS + 35, 30);
    text->DrawText(std::to_string(bestScore),SCORE_BOARD_X_POS + 130, SCORE_BOARD_Y_POS + 35, 30);
    text->DrawText("Level: ",SCORE_BOARD_X_POS, SCORE_BOARD_Y_POS + 70, 30);
    text->DrawText(std::to_string(level),SCORE_BOARD_X_POS + 130, SCORE_BOARD_Y_POS + 70, 30);
    text->DrawText("Time survived: ",SCORE_BOARD_X_POS, SCORE_BOARD_Y_POS + 105, 30);
    text->DrawText(std::to_string((timer.getSeconds())),SCORE_BOARD_X_POS + 300, SCORE_BOARD_Y_POS + 105, 30);
    SDL_RenderPresent(renderer);
}

void Game::RenderLaser()
{
    SDL_Rect renderRect;
    SDL_Rect clipRect;
    setRectSize(clipRect, frame % 2, 0, 80, 160);
    setRectSize(renderRect, pos - SCREEN_HEIGHT / 4 , 0, SCREEN_HEIGHT / 2, SCREEN_HEIGHT);
    SDL_RenderCopy(renderer, laserTexture, &clipRect, &renderRect);
}

void Game::RenderWarning()
{
    SDL_Rect renderRect;
    setRectSize(renderRect, pos - 40, 40, 50, 50);
    if((frame / 20) % 2 == 0){
        SDL_RenderCopy(renderer, warningTexture, NULL, &renderRect);
        //SDL_RenderDrawRect(renderer,&laserHitbox);
    }
}

bool Game::NewLaser()
{
    if(frame % ( LASER_SPAWN_RATE ) == 0 && frame != 0){
        laserOn = 1;
        laserTimer.start();
        pos = Spaceship->x + Spaceship->width / 2;
        setRectSize(laserHitbox, pos - SCREEN_HEIGHT / 8 , 0, SCREEN_HEIGHT / 4 - 45, SCREEN_HEIGHT);
        return 1;
    }
    return 0;
}

//test
bool Game::NewBoss()
{
    if(bossTimer.getSeconds() == BOSS_SPAWN_TIME){
//        if(boss != NULL)
//            delete boss;
        boss = new Boss(renderer,level,bossTexture);
        bossTimer.stop();
        hasBoss = 1;
        return 1;
    }
    return 0;
}
//end test



void Game::Update()
{
    if(Spaceship->livesLeft == 0){
        SDL_Delay(1000);
        Spaceship->died = true;
    }

    HandleInput();
    updateLevel();

    if(frame % obstaclesSpawnRate == 0){
        obstacle = new Obstacles(renderer, obstacleMoveSpeed);
		obstaclesList.push_back(obstacle);
    }

    if(frame % coinSpawnRate == 0){
        coinCounted++;
        coin = new Coin(renderer, coinCounted);
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
    UpdateList();
    if(NewBoss() || hasBoss){
        boss->Update();
        if(frame % BOSS_SHOOT_RATE == 0 && boss->alive){
            boss->LoadBullet(Spaceship->getMainHitBox());
            audio->playSound("sound/bossShoot.wav",soundOn,40);
        }
    }
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
        if( Spaceship->RemainCooldown() == SHOOT_COOLDOWN ){
            bullet = new Bullet(renderer, Spaceship->getMainHitBox());
            bulletList.push_back(bullet);
            Spaceship->lastShootTime = SDL_GetTicks();
        }
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
    {
        if( Spaceship->RemainCooldownSpecial() == SPECIAL_COOLDOWN ){
            bullet = new Bullet(renderer, Spaceship->getMainHitBox(),specialBulletTexture);
            bulletList.push_back(bullet);
            Spaceship->lastSpecialShoot = SDL_GetTicks();
            Spaceship->reduceCooldown = 0;
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

template <typename Container>
void Game::UpdateList(std::list<Container> &checklist){
    typename std::list<Container>::iterator current = checklist.begin();
    while (current != checklist.end()){
        //Check if off screen
        if ((*current)->Box.y > SCREEN_HEIGHT)
        {
            delete(*current);
            // erase returns the iterator following the last removed element
            current = checklist.erase(current);
        }
        else {
            (*current)->Update();
            ++current;
        }
    }
}

template <typename Container>
void Game::ClearList(std::list<Container> &checklist)
{
    if(!checklist.empty()){
            checklist.erase(checklist.begin(),checklist.end());
	}
}

void Game::UpdateList()
{
    UpdateList<Star*>(starList);
    UpdateList<Star*>(largeStarList);
    UpdateList<Coin*>(coinList);
    UpdateList<Background*>(backgroundList);
    UpdateList<Bullet*>(bulletList);
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
}

void Game::increaseScore(const int scoreGet)
{
    score += scoreGet;
    if(score >= bestScore) {
        bestScore = score;
    }
}

void Game::Quit()
{
    freePointers();
    SDL_DestroyTexture(bossTexture);
    SDL_DestroyTexture(specialBulletTexture);
    //save best score
    file = SDL_RWFromFile( "bestscore.bin", "w+b" );
    SDL_RWwrite( file, &bestScore, sizeof(Sint32), 1 );
    SDL_RWclose( file );

    //quit systems
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}

void Game::PauseHandle()
{
    if(isPause) {
        if(pauseMenu->resume) {
            pauseMenu->resume = 0;
            Mix_ResumeMusic();
            Mix_Resume(-1);
            isPause = 0;
            timer.unpause();
            bossTimer.unpause();
            laserTimer.unpause();
        }

    }
    else {
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            Mix_PauseMusic();
            Mix_Pause(-1);
            isPause = 1;
            timer.pause();
            bossTimer.pause();
            laserTimer.pause();
        }
    }
}

void Game::updateLevel()
{
    //increase spawn rate of obstacles
    if(frame % (TIME_TO_NEXT_LEVEL*60) == 0) {
        obstaclesSpawnRate--;
        levelUpdate1 = 1;
        if(obstaclesSpawnRate < MIN_OBSTACLE_SPAWN_RATE) {
            obstaclesSpawnRate = MIN_OBSTACLE_SPAWN_RATE;
        }
    }

    //increase speed of the game
    if(score / SCORE_TO_SPEED_UP > lastIncreaseSpeed) {
        obstacleMoveSpeed += 0.5 * (score/SCORE_TO_SPEED_UP);
        lastIncreaseSpeed++;
        levelUpdate2 = 1;
        if(obstacleMoveSpeed > MAX_OBSTACLE_SPEED) {
            obstacleMoveSpeed = MAX_OBSTACLE_SPEED;
        }
    }
    if(levelUpdate1 && levelUpdate2){
        level++;
        levelUpdate1 = 0;
        levelUpdate2 = 0;
    }
}

void Game::GameOver()
{
    Mix_HaltMusic();
    quitMenu->HandleMenuEvent(event);
    quitMenu->RenderMenu(frame);
    if(quitMenu->playAgain) {
        NewGame();
        SDL_Delay(50);
    }
    if(quitMenu->quitGame) {
        quit = true;
    }
}

void Game::Pause()
{
    pauseMenu->GetSoundState(soundOn);
    pauseMenu->HandleMenuEvent(event);
    pauseMenu->RenderMenu();
    if(pauseMenu->quitGame){
        quit = true;
    }
    if(pauseMenu->soundChange){
        soundOn = !soundOn;
        pauseMenu->soundChange = false;
    }
}

void Game::StartGame()
{
    mainMenu->HandleMenuEvent(event);
    mainMenu->RenderMenu(bestScore);
    if(mainMenu->quitGame) {
        quit = true;
    }
    if(mainMenu->resetHighscore) {
        bestScore = 0;
        mainMenu->resetHighscore = false;
    }
    if(mainMenu->soundChange){
        soundOn = !soundOn;
        mainMenu->soundChange = false;
    }
}

void Game::freePointers()
{
    delete boss;
    delete quitMenu;
    delete mainMenu;
    delete pauseMenu;
    delete Spaceship;
    delete energyBar;
    delete healthBar;
    delete explosion;
    delete text;
    delete audio;
}
