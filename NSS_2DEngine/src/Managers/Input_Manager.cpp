#include "Input_Manager.h"

Input_Manager* Input_Manager::instance = nullptr;

Input_Manager* Input_Manager::GetInstance()
{
	if (!instance)
	{
		instance = new Input_Manager();
	}

	return instance;
}

Input_Manager::~Input_Manager()
{
	ClearKeyboardBindings();
	ClearMouseBindings();
	delete instance;
}

void Input_Manager::AddKeyboardBinding(sf::Keyboard::Key key, std::function<void()> callback, bool pressed)
{
	if (keyboardKeys.find(key) == keyboardKeys.end())
	{
		if (pressed)
		{
			keyboardKeys.insert(std::make_pair(key, new InputCallback(callback, nullptr)));
		}
		else
		{
			keyboardKeys.insert(std::make_pair(key, new InputCallback(nullptr, callback)));
		}
	}
}

void Input_Manager::AddKeyboardBinding(sf::Keyboard::Key key, std::function<void()> pressedCallback, std::function<void()> releasedCallback)
{
	if (keyboardKeys.find(key) == keyboardKeys.end())
	{
		keyboardKeys.insert(std::make_pair(key, new InputCallback(pressedCallback, releasedCallback)));
	}
}

void Input_Manager::ClearKeyboardBindings()
{
	for (auto& keyboardKey : keyboardKeys)
	{
		delete keyboardKey.second;
		keyboardKey.second = nullptr;
	}

	keyboardKeys.clear();
}

void Input_Manager::RemoveKeyboardBinding(sf::Keyboard::Key key)
{
	if (keyboardKeys.find(key) != keyboardKeys.end())
	{
		keyboardKeys.erase(key);
	}
}

void Input_Manager::AddMouseBinding(sf::Mouse::Button button, std::function<void()> callback, bool pressed)
{
	if (mouseButtons.find(button) == mouseButtons.end())
	{
		if (pressed)
		{
			mouseButtons.insert(std::make_pair(button, new InputCallback(callback, nullptr)));
		}
		else
		{
			mouseButtons.insert(std::make_pair(button, new InputCallback(nullptr, callback)));
		}
	}
}

void Input_Manager::AddMouseBinding(sf::Mouse::Button button, std::function<void()> pressedCallback, std::function<void()> releasedCallback)
{
	if (mouseButtons.find(button) == mouseButtons.end())
	{
		mouseButtons.insert(std::make_pair(button, new InputCallback(pressedCallback, releasedCallback)));
	}
}

void Input_Manager::ClearMouseBindings()
{
	for (auto& mouseButton : mouseButtons)
	{
		delete mouseButton.second;
		mouseButton.second = nullptr;
	}

	mouseButtons.clear();
}

void Input_Manager::RemoveMouseBinding(sf::Mouse::Button button)
{
	if (mouseButtons.find(button) != mouseButtons.end())
	{
		mouseButtons.erase(button);
	}
}

void Input_Manager::HandleEvents(sf::Event newEvent)
{
	auto key = keyboardKeys.find(newEvent.key.code);
	if (key != keyboardKeys.end())
	{
		if (newEvent.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(newEvent.key.code))
			{
				key->second->pressedCallback();
			}

			if (key->second->pressedCallback != nullptr)
			{
				key->second->pressedCallback();
			}
		}
		else if (newEvent.type == sf::Event::KeyReleased)
		{
			if (key->second->releasedCallback != nullptr)
			{
				key->second->releasedCallback();
			}
		}
	}

	auto button = mouseButtons.find(newEvent.mouseButton.button);
	if (button != mouseButtons.end())
	{
		if (newEvent.type == sf::Event::MouseButtonPressed)
		{
			if (button->second->pressedCallback != nullptr)
			{
				button->second->pressedCallback();
			}
		}
		else if (newEvent.type == sf::Event::MouseButtonReleased)
		{
			if (button->second->releasedCallback != nullptr)
			{
				button->second->releasedCallback();
			}
		}
	}
}
