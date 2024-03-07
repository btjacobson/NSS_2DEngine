#include "App.h"

#include <iostream>

App::App() : window(sf::VideoMode(800, 600), "Test")
{

}

void App::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate = clock.restart();

		HandleEvents();
		Update(timeSinceLastUpdate.asSeconds());
		Render();
	}
}

void App::HandleEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		Input_Manager::GetInstance()->HandleEvents(event);
	}
}

void App::Update(float dt)
{
	State_Manager::GetInstance()->Update(dt);
	GUI_Manager::GetInstance()->Update(dt);
	Timer_Manager::GetInstance()->Update(dt);
	Entity_Manager::GetInstance()->Update(dt);
}

void App::Render()
{
	window.clear();
	State_Manager::GetInstance()->Draw(&window);
	Entity_Manager::GetInstance()->Draw(&window);
	GUI_Manager::GetInstance()->Draw(&window);
	window.display();
}
