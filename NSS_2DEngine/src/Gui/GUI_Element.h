#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <SFML/Graphics.hpp>

class GUI_Element
{
public:
	GUI_Element(sf::Vector2f position, sf::Vector2f size);

	virtual void Update(float dt) = 0;
	
	void SetSprite(sf::Texture* texture);

	sf::Sprite* GetSprite();

private:
	sf::Sprite sprite;
};

#endif