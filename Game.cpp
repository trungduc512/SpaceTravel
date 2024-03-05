#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
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
//	delete Spaceship; // this is use only to create new game
	Spaceship = new SpaceShip(renderer);
}
void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    Spaceship->Render();
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
            if( event.type == SDL_QUIT ) quit = true;

        }
        HandleInput();
        Render();
    }
    delete Spaceship;
    Quit();
}

void Game::HandleInput()
{
    //default have only 2 movements (left & right)
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

void Game::Quit()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
}

