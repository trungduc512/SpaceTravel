#ifndef USEFULFUNCTIONS_H_INCLUDED
#define USEFULFUNCTIONS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

void setRectSize(SDL_Rect &rect, float x, float y, float w, float h);
bool range(int &compare, const int min, const int max);
void getTexture( SDL_Texture* &texture, SDL_Renderer* renderer, std::string path, Uint8 r, Uint8 g, Uint8 b );
void getTexture( SDL_Texture* &texture, SDL_Renderer* renderer, std::string path, Uint8 r, Uint8 g, Uint8 b , float &width, float &height );
// Define a structure for a point (vertex)
struct Point {
    double x, y;
};

// Define a structure for an edge
struct Edge {
    int from, to;
    double weight;
};

struct EdgeForDijkstra {
    int v;
    double w;
};
#endif // USEFULFUNCTIONS_H_INCLUDED
