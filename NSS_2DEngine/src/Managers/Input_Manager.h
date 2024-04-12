#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <unordered_map>

struct InputCallback
{
	InputCallback(std::function<void()> pressed, std::function<void()> released)
	{
		pressedCallback = pressed;
		releasedCallback = released;
	}

	std::function<void()> pressedCallback;
	std::function<void()> releasedCallback;
};

class Input_Manager
{
public:
	static Input_Manager* GetInstance();

	~Input_Manager();

	void AddKeyboardBinding(sf::Keyboard::Key key, std::function<void()> callback, bool pressed);
	void AddKeyboardBinding(sf::Keyboard::Key key, std::function<void()> pressedCallback, std::function<void()> releasedCallback);
	void ClearKeyboardBindings();
	void RemoveKeyboardBinding(sf::Keyboard::Key key);

	void AddMouseBinding(sf::Mouse::Button button, std::function<void()> callback, bool pressed);
	void AddMouseBinding(sf::Mouse::Button button, std::function<void()> pressedCallback, std::function<void()> releasedCallback);
	void ClearMouseBindings();
	void RemoveMouseBinding(sf::Mouse::Button button);

	void HandleEvents(sf::Event newEvent);
	void Update();

private:
	Input_Manager() = default;
	Input_Manager(Input_Manager&) {}
	void operator=(Input_Manager const&) const {}

	static Input_Manager* instance;

	std::unordered_map<sf::Keyboard::Key, InputCallback*> _keyboardKeys;
	std::unordered_map<sf::Mouse::Button, InputCallback*> _mouseButtons;
	std::unordered_map<sf::Keyboard::Key, sf::Event::EventType> _keyboardEvents;
	std::unordered_map<sf::Mouse::Button, sf::Event::EventType> _mouseEvents;
};

#endif
