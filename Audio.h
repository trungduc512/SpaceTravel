#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <SDL_mixer.h>
#include <string>

class Audio
{
public:
	Audio();
	~Audio();

	void playSound(std::string filePath, bool soundOn);
};

#endif // AUDIO_H_INCLUDED
