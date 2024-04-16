#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "MovingObject.h"

class Background : public MovingObject
{
public:
    Background(SDL_Renderer* renderer);
    Background(SDL_Renderer* renderer, int type, float x_pos, float y_pos);
    ~Background();

    void getRandomBackGround();
    void Render();
    void Update();
    void LoadType(int type);
    void SetPos( float x_pos, float y_pos);
    int getType();
    int pathnum;

private:
    SDL_Texture* texture;
    std::string path;
};

#endif // BACKGROUND_H_INCLUDED
