#include "Audio.h"

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::playSound(std::string filePath, bool soundOn)
{
    if(soundOn){
        Mix_Chunk* audioChunk = Mix_LoadWAV(filePath.c_str());
        Mix_VolumeChunk(audioChunk, 60);
        Mix_PlayChannel(-1, audioChunk, 0);
    }
}
