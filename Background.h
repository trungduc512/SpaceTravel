#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "MovingObject.h"

class Background : public MovingObject
{
public:
    Background(SDL_Renderer* renderer);
    ~Background();

    void getRandomBackGround();
    void Render();
    void Update();

private:
    SDL_Texture* texture;
    std::string path;
};

#endif // BACKGROUND_H_INCLUDED
