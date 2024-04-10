#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

class Mouse : public Object
{
private:
public:
	SDL_Rect cursor, tip;

	Mouse();
	~Mouse();
	void Render();
};

#endif // MOUSE_H_INCLUDED
