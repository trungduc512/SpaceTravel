#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

#include "MovingObject.h"

class Obstacles : public MovingObject
{
public:
    Obstacles(SDL_Renderer *renderer, float speed);
    ~Obstacles();

    void Render();
    void Update();
    bool isCollided(const SDL_Rect* leftHitBox, const SDL_Rect* rightHitBox, const SDL_Rect* mainHitBox);
    void getRandomImage();
    SDL_Rect* getHitBox();
    std::string getPath();

private:
    SDL_Rect Hitbox;
    SDL_Texture* texture;
    std::string path;
};


#endif // OBSTACLES_H_INCLUDED
