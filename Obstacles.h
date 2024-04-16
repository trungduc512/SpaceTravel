#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

#include "MovingObject.h"

class Obstacles : public MovingObject
{
public:
    Obstacles(SDL_Renderer *renderer, float speed);
    Obstacles(SDL_Renderer *renderer, float speed, int type, float x_pos, float y_pos);
    ~Obstacles();

    void Render();
    void Update();
    void getRandomImage();
    SDL_Rect* getHitBox();
    std::string getPath();
    int getType();
    void SetPos(float x_pos, float y_pos);
    void SetType(int type);
    float getSpeed();

private:
    SDL_Rect Hitbox;
    SDL_Texture* texture;
    std::string path;
    int obstacleType;
};


#endif // OBSTACLES_H_INCLUDED
