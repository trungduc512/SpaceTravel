#include "HUD.h"

HUD::HUD(SDL_Renderer* renderer, std::string path) : Object(renderer)
{
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 69, 69, 69));
    texture = SDL_CreateTextureFromSurface(renderer, newSurface);
    SDL_FreeSurface(newSurface);
}

HUD::~HUD()
{
    SDL_DestroyTexture(texture);
}

void HUD::RenderEnergyBar(int cooldownTime)
{
    if(cooldownTime == SHOOT_COOLDOWN){
        cooldownTime = 4;
    }
    else{
        cooldownTime =(cooldownTime / (SHOOT_COOLDOWN/5))%5;
    }
    setRectSize(renderBox, 1698, 50, 100, 50);
    setRectSize(renderClip, 0, cooldownTime * 200, 380, 200);
    SDL_RenderCopy(renderer, texture, &renderClip, &renderBox);
}

void HUD::RenderHealthBar(unsigned int livesLeft)
{
    if (livesLeft != 0) {
        // Calculate the dimensions for the health bar
        int barWidth = livesLeft * 30;
        int clipWidth = livesLeft * 160;

        // Set the position and size of the health bar
        setRectSize(renderBox, 1700, 25, barWidth, 30);
        setRectSize(renderClip, 0, 0, clipWidth, 160);

        // Render the health bar texture
        SDL_RenderCopy(renderer, texture, &renderClip, &renderBox);
    }
}
