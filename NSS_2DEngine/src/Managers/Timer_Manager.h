#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <functional>
#include <unordered_map>

#include "../Core/Timer.h"

class Timer_Manager
{
public:
	static Timer_Manager* GetInstance();

	~Timer_Manager();

	void AddTimer(float timeInSeconds, std::function<void()> callback);
	void AddTickTimer(float timeInSeconds, float tickInSeconds, std::function<void()> callback);
	void Update(float dt);

private:
	Timer_Manager() = default;
	Timer_Manager(Timer_Manager&) {}
	void operator=(Timer_Manager const&) const {}

	static Timer_Manager* instance;

	void PurgeDeadTimers();

	std::unordered_map<Timer*, std::function<void()>> timers;
	bool purge = false;
};
#endif
