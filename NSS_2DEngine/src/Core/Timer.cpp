#include "Timer.h"

Timer::Timer(float timeInSeconds, float tickInSeconds, bool tickTimer) : tick(tickTimer)
{
	totalTime = timeInSeconds;
	tickTime = tickInSeconds;
	currentTime = 0.0f;
}

void Timer::Update(float dt)
{
	if (tick)
	{
		currentTime += dt;
	}
	else
	{
		totalTime -= dt;
	}
}

bool Timer::Finished()
{
	return totalTime <= 0;
}

bool Timer::Tick()
{
	return tick;
}

bool Timer::CheckTick()
{
	if (currentTime >= tickTime)
	{
		totalTime -= currentTime;
		currentTime = 0;

		return true;
	}
	else
	{
		return false;
	}
}
