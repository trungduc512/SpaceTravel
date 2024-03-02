#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class Object
{
public:
    Object(SDL_Renderer* renderer);
    ~Object();

    float x_pos;
    float y_pos;
    float width;
    float height;
};

#endif // OBJECT_H_INCLUDED
