#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <SDL.h>
class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();
	void setSavedTicks( Uint32 save );

	Uint32 getTicks();
	Uint32 getStartTicks();
	Uint32 getPauseTicks();
	Uint32 getSaveTicks();

	int getSeconds();

	bool isStarted();
	bool isPaused();

private:
    Uint32 startTicks;
	Uint32 pausedTicks;
	Uint32 savedTicks;
	bool paused;
	bool started;
};

#endif // TIMER_H_INCLUDED
