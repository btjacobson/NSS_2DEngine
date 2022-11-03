#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "../Gui/GUI_Element.h"
#include "../Gui/Button.h"

class GUI_Manager
{
public:
	static GUI_Manager* GetInstance();

	~GUI_Manager();

	void AddGUIElement(std::string name, GUI_Element* element);
	void RemoveGUIElement(std::string name);
	void ClearGUIElements();
	
	void Update(float dt);
	void Draw(sf::RenderWindow* window);

	GUI_Element* GetGUIElement(std::string name);

private:
	GUI_Manager() = default;
	GUI_Manager(GUI_Manager&) {}
	void operator=(GUI_Manager const&) const {}

	static GUI_Manager* instance;

	std::unordered_map<std::string, GUI_Element*> elements;
};

#endif
