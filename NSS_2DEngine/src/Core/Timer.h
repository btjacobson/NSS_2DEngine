#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer(float timeInSeconds, float tickInSeconds = 0.0f, bool tickTimer = false);

	void Update(float dt);

	bool Finished();
	bool Tick();
	bool CheckTick();

private:
	float totalTime;
	float tickTime;
	float currentTime;
	bool tick;
};

#endif