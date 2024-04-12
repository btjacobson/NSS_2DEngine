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
	if (_keyboardKeys.find(key) == _keyboardKeys.end())
	{
		if (pressed)
		{
			_keyboardKeys.insert(std::make_pair(key, new InputCallback(callback, nullptr)));
		}
		else
		{
			_keyboardKeys.insert(std::make_pair(key, new InputCallback(nullptr, callback)));
		}
	}
}

void Input_Manager::AddKeyboardBinding(sf::Keyboard::Key key, std::function<void()> pressedCallback, std::function<void()> releasedCallback)
{
	if (_keyboardKeys.find(key) == _keyboardKeys.end())
	{
		_keyboardKeys.insert(std::make_pair(key, new InputCallback(pressedCallback, releasedCallback)));
	}
}

void Input_Manager::ClearKeyboardBindings()
{
	for (auto& keyboardKey : _keyboardKeys)
	{
		delete keyboardKey.second;
		keyboardKey.second = nullptr;
	}

	_keyboardKeys.clear();
}

void Input_Manager::RemoveKeyboardBinding(sf::Keyboard::Key key)
{
	if (_keyboardKeys.find(key) != _keyboardKeys.end())
	{
		_keyboardKeys.erase(key);
	}
}

void Input_Manager::AddMouseBinding(sf::Mouse::Button button, std::function<void()> callback, bool pressed)
{
	if (_mouseButtons.find(button) == _mouseButtons.end())
	{
		if (pressed)
		{
			_mouseButtons.insert(std::make_pair(button, new InputCallback(callback, nullptr)));
		}
		else
		{
			_mouseButtons.insert(std::make_pair(button, new InputCallback(nullptr, callback)));
		}
	}
}

void Input_Manager::AddMouseBinding(sf::Mouse::Button button, std::function<void()> pressedCallback, std::function<void()> releasedCallback)
{
	if (_mouseButtons.find(button) == _mouseButtons.end())
	{
		_mouseButtons.insert(std::make_pair(button, new InputCallback(pressedCallback, releasedCallback)));
	}
}

void Input_Manager::ClearMouseBindings()
{
	for (auto& mouseButton : _mouseButtons)
	{
		delete mouseButton.second;
		mouseButton.second = nullptr;
	}

	_mouseButtons.clear();
}

void Input_Manager::RemoveMouseBinding(sf::Mouse::Button button)
{
	if (_mouseButtons.find(button) != _mouseButtons.end())
	{
		_mouseButtons.erase(button);
	}
}

void Input_Manager::HandleEvents(sf::Event newEvent)
{
	if (newEvent.type == sf::Event::KeyPressed || newEvent.type == sf::Event::KeyReleased)
	{
		auto key = _keyboardEvents.find(newEvent.key.code);
		if (key != _keyboardEvents.end())
		{
			key->second = newEvent.type;
		}
		else
		{
			_keyboardEvents.emplace(std::pair(newEvent.key.code, newEvent.type));
		}
	}

	/*if (newEvent.type == sf::Event::MouseButtonPressed || newEvent.type == sf::Event::MouseButtonReleased)
	{
		auto button = _mouseEvents.find(newEvent.mouseButton.button);
		if (button != _mouseEvents.end())
		{
			button->second = newEvent.type;
		}
		else
		{
			_mouseEvents.emplace(std::pair(newEvent.mouseButton.button, newEvent.type));
		}
	}*/
}

void Input_Manager::Update()
{
	for (auto it = _keyboardEvents.begin(); it != _keyboardEvents.end();)
	{
		sf::Keyboard::Key keyEvent = it->first;
		sf::Event::EventType typeEvent = it->second;

		auto key = _keyboardKeys.find(keyEvent);
		if (key != _keyboardKeys.end())
		{
			switch (typeEvent)
			{
			case sf::Event::KeyPressed:
				if (key->second->pressedCallback != nullptr)
				{
					key->second->pressedCallback();
				}
				break;

			case sf::Event::KeyReleased:
				if (key->second->releasedCallback != nullptr)
				{
					key->second->releasedCallback();
				}
				break;
			}

			it = _keyboardEvents.erase(it);
		}
	}
}
