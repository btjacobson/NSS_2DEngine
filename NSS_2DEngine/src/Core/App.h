#ifndef APP_H
#define APP_H

#include "SFML/Graphics.hpp"

#include "../Managers/State_Manager.h"
#include "../Managers/Timer_Manager.h"
#include "../Managers/GUI_Manager.h"
#include "../Managers/Entity_Manager.h"
#include "../Managers/Input_Manager.h"

class App
{
public:
	App();

	void Run();

private:
	void HandleEvents();
	void Update(float dt);
	void Render();

	sf::RenderWindow window;
};

#endif
