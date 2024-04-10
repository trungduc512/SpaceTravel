#include "Boss.h"

Boss::Boss(SDL_Renderer *renderer,unsigned int level) : MovingObject(renderer)
{
    getTexture(texture, renderer, "image/boss.png", 69, 69, 69, width, height);
    getTexture(healthBarTexture, renderer, "image/Boss_health_bar.png", 69, 69, 69);
    moveSpeed = 3;
    x_movespeed = 5;
    appear = 0;
    setRectSize(Hitbox, rand()%(SCREEN_WIDTH - (int)width), -100, width, height);
    alive = 1;
    livesLeft = BOSS_BASE_HEALTH + level * BOSS_SCALE_HEALTH;
    firstLivesLeft = livesLeft;
}

Boss::~Boss()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(healthBarTexture);
}

void Boss::Render()
{
    setRectSize(ClipBox, 0, 0, livesLeft * (700 / firstLivesLeft), 188 ); // width 700, height 188
    setRectSize(HealthBarBox,Hitbox.x + 50, Hitbox.y + 175, livesLeft * (150 / firstLivesLeft), 10); // suit
    SDL_RenderCopy(renderer,texture,NULL,&Hitbox);
    if(alive)
        SDL_RenderCopy(renderer,healthBarTexture,&ClipBox,&HealthBarBox);
    for(Bullet* currentBossBullet : bossBulletList){
        currentBossBullet->RenderEx();
    }
}

void Boss::Update()
{
    if(alive){
        Hitbox.x += x_movespeed;
        Hitbox.y += moveSpeed;
        if(Hitbox.y >= BOSS_MIN_Y_POS) appear = 1;
        if((Hitbox.y >= BOSS_MIN_Y_POS || Hitbox.y < 0) && appear){
            moveSpeed = -moveSpeed;
        }
        if(Hitbox.x < 0 || Hitbox.x + Hitbox.w >= SCREEN_WIDTH){
            x_movespeed = -x_movespeed;
        }
        setRectSize(Hitbox, Hitbox.x, Hitbox.y, width, height);
    }
    else{
        Hitbox.y -= 1;
        setRectSize(Hitbox, Hitbox.x, Hitbox.y, width, height);
    }
    //
    std::list<Bullet*>::iterator currentBossBullet = bossBulletList.begin();
    while (currentBossBullet != bossBulletList.end()){
        //Check if obstacle is off screen
        if ((*currentBossBullet)->Box.y > SCREEN_HEIGHT)
        {
            delete(*currentBossBullet);
            // erase returns the iterator following the last removed element
            currentBossBullet = bossBulletList.erase(currentBossBullet);
        }
        else {
            (*currentBossBullet)->UpdateEx();
            ++currentBossBullet;
        }
    }
}

void Boss::DecreaseLives()
{
    livesLeft--;
    if(livesLeft <= 0){
        alive = 0;
    }
}

SDL_Rect* Boss::getHitBox()
{
    return &Hitbox;
}

void Boss::LoadBullet(const SDL_Rect *mainHitbox)
{
    bossBullet = new Bullet(renderer, &Hitbox, getAngle(mainHitbox));
    bossBulletList.push_back(bossBullet);
}

double Boss::getAngle(const SDL_Rect *mainHitbox)
{
    SDL_Point bossCentre = {Hitbox.x + Hitbox.w / 2, Hitbox.y + Hitbox.h / 2};
    SDL_Point spaceshipCentre = {mainHitbox->x + mainHitbox->w / 2, mainHitbox->y + mainHitbox->h / 2};
    return atan2( (spaceshipCentre.x - bossCentre.x) , (spaceshipCentre.y - bossCentre.y) );
}
