#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
    Game* game = new Game();
    if( game -> Init() )
        game -> Run();
    delete game;
    return 0;
}
