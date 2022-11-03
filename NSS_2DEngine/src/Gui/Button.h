#ifndef BUTTON_H
#define BUTTON_H

#include "GUI_Element.h"

class Button : public GUI_Element
{
public:
	Button(sf::Vector2f position, sf::Vector2f size);

	void Update(float dt);

private:

};

#endif 