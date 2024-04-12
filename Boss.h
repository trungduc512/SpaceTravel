#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "MovingObject.h"
#include "Bullet.h"
#include <list>
#include <cmath>

class Boss : public MovingObject
{
public:
    Boss(SDL_Renderer *renderer, unsigned int level, SDL_Texture* pre_creatingTexture);
    ~Boss();

    int livesLeft;
    int firstLivesLeft;
    bool alive;
    std::list<Bullet*> bossBulletList;

    void Render();
    void Render(unsigned int frame);
    void Update();
    void Shoot();
    void LoadBullet(const SDL_Rect *mainHitbox);
    double getAngle(const SDL_Rect *mainHitbox);
    void DecreaseLives(int damage);
    SDL_Rect* getHitBox();

private:
    SDL_Rect Hitbox;
    SDL_Rect RenderBox;
    SDL_Rect bossClipBox;
    SDL_Rect ClipBox;
    SDL_Rect HealthBarBox;
    SDL_Texture* texture;
    SDL_Texture* healthBarTexture;
    Bullet* bossBullet;
    double angle;
    float x_movespeed;
    bool appear;
};

#endif // BOSS_H_INCLUDED
