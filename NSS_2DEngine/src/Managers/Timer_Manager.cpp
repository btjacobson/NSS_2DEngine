#include "Timer_Manager.h"

Timer_Manager* Timer_Manager::instance = nullptr;

Timer_Manager* Timer_Manager::GetInstance()
{
	if (!instance)
	{
		instance = new Timer_Manager();
	}

	return instance;
}

Timer_Manager::~Timer_Manager()
{
	delete instance;
}

void Timer_Manager::AddTimer(float timeInSeconds, std::function<void()> callback)
{
	Timer* tTimer = new Timer(timeInSeconds);
	timers.insert(std::make_pair(tTimer, callback));
}

void Timer_Manager::AddTickTimer(float timeInSeconds, float tickInSeconds, std::function<void()> callback)
{
	Timer* tTimer = new Timer(timeInSeconds, tickInSeconds, true);
	timers.insert(std::make_pair(tTimer, callback));
}

void Timer_Manager::Update(float dt)
{
	for (auto timer : timers)
	{
		timer.first->Update(dt);
		if (timer.first->Tick())
		{
			if (timer.first->CheckTick())
			{
				timer.second();
			}
		}

		if (timer.first->Finished())
		{
			purge = true;
		}
	}

	if (purge)
	{
		PurgeDeadTimers();
	}
}

void Timer_Manager::PurgeDeadTimers()
{
	for (auto timer = timers.begin(); timer != timers.end();)
	{
		if ((*timer).first->Finished())
		{
			if (!((*timer).first->Tick()))
			{
				(*timer).second();
			}

			timer = timers.erase(timer);
		}
		else
		{
			++timer;
		}
	}
}
