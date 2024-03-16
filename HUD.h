#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "Object.h"

class HUD : public Object
{
public:
    HUD(SDL_Renderer* renderer, std::string path);
    ~HUD();

    void RenderEnergyBar(int cooldownTime);
    void RenderHealthBar(unsigned int livesLeft);

private:
    SDL_Texture* texture;
    SDL_Rect renderBox;
    SDL_Rect renderClip;
};

#endif // HUD_H_INCLUDED
