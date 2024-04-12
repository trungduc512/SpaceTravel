#include "Boss.h"

Boss::Boss(SDL_Renderer *renderer, unsigned int level, SDL_Texture* pre_creatingTexture) : MovingObject(renderer)
{
    texture = pre_creatingTexture;
    width = 400;
    height = 400;
    getTexture(healthBarTexture, renderer, "image/Boss_health_bar.png", 69, 69, 69);
    moveSpeed = 3;
    x_movespeed = 5;
    appear = 0;
    setRectSize(RenderBox, rand()%(SCREEN_WIDTH - (int)width), -400, width, height);
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
    setRectSize(HealthBarBox,RenderBox.x + 50, RenderBox.y + 175, livesLeft * (150 / firstLivesLeft), 10); // suit
    SDL_RenderCopy(renderer,texture,NULL,&Hitbox);
    if(alive)
        SDL_RenderCopy(renderer,healthBarTexture,&ClipBox,&HealthBarBox);
    for(Bullet* currentBossBullet : bossBulletList){
        currentBossBullet->RenderEx();
    }
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderDrawRect(renderer,&RenderBox);
}

void Boss::Render(unsigned int frame)
{
    setRectSize(bossClipBox, 0, ((frame / 5)%34) * 400, 400, 400);
    setRectSize(ClipBox, 0, 0, livesLeft * (700 / firstLivesLeft), 188 ); // width 700, height 188
    setRectSize(HealthBarBox,RenderBox.x + 50, RenderBox.y + 175, livesLeft * (150 / firstLivesLeft), 10); // suit
    SDL_RenderCopy(renderer,texture,&bossClipBox,&RenderBox);
    if(alive)
        SDL_RenderCopy(renderer,healthBarTexture,&ClipBox,&HealthBarBox);
    for(Bullet* currentBossBullet : bossBulletList){
        currentBossBullet->RenderEx();
    }
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderDrawRect(renderer,&RenderBox);
//    SDL_RenderDrawRect(renderer,&Hitbox);
}

void Boss::Update()
{
    if(alive){
        RenderBox.x += x_movespeed;
        RenderBox.y += moveSpeed;
        if(RenderBox.y >= BOSS_MIN_Y_POS) appear = 1;
        if((RenderBox.y >= BOSS_MIN_Y_POS || RenderBox.y < 0) && appear){
            moveSpeed = -moveSpeed;
        }
        if(RenderBox.x < 0 || RenderBox.x + RenderBox.w >= SCREEN_WIDTH){
            x_movespeed = -x_movespeed;
        }
        setRectSize(RenderBox, RenderBox.x, RenderBox.y, width, height);
    }
    else{
        RenderBox.y -= 1;
        setRectSize(RenderBox, RenderBox.x, RenderBox.y, width, height);
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
    setRectSize(Hitbox, RenderBox.x + 40, RenderBox.y, RenderBox.w - 100, RenderBox.h - 50);
}

void Boss::DecreaseLives(int damage)
{
    livesLeft -= damage;
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
