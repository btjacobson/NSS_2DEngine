#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include "../Managers/Asset_Manager.h"
#include "../Managers/Timer_Manager.h"
#include "../Managers/GUI_Manager.h"
#include "../Managers/Entity_Manager.h"
#include "../Managers/Input_Manager.h"

class State
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	void SetActive(bool active) 
	{
		isActive = active;
	};

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;

	virtual bool IsActive() = 0;

protected:
	bool isActive = false;
};

#endif
