#include "Timer.h"

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	savedTicks = 0;

	paused = false;
	started = false;
}

void Timer::start()
{
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::stop()
{
	started = false;
	paused = false;

	startTicks = 0;
	pausedTicks = 0;
	savedTicks = 0;
}

void Timer::pause()
{
    if( started && !paused)
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
	if (started && paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

void Timer::setSavedTicks( Uint32 save )
{
    savedTicks = save;
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTicks + savedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks + savedTicks;
		}
	}

	return time;
}

Uint32 Timer::getStartTicks()
{
    return startTicks;
}

Uint32 Timer::getPauseTicks()
{
    return pausedTicks;
}

Uint32 Timer::getSaveTicks()
{
    return savedTicks;
}

int Timer::getSeconds()
{
    Uint32 time = getTicks();
    return time / 1000;
}

bool Timer::isStarted()
{
	return started;
}

bool Timer::isPaused()
{
	return paused && started;
}
