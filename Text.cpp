#include "Text.h"

Text::Text(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Text::DrawText(std::string text, int x, int y, int fontSize)
{
	TTF_Font* font = TTF_OpenFont("font/JackPixel.ttf", fontSize);

	SDL_Color fg = { 255,255,255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fg);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect sizeRect;
	setRectSize(sizeRect, 0, 0, surface->w, surface->h);

	SDL_Rect posRect;
	setRectSize(posRect, x, y, sizeRect.w, sizeRect.h);

	SDL_RenderCopy(renderer, texture, &sizeRect, &posRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}
