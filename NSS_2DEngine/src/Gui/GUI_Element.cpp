#include "GUI_Element.h"

GUI_Element::GUI_Element(sf::Vector2f position, sf::Vector2f size)
{
	sprite = sf::Sprite();
	sprite.setPosition(position);
}

void GUI_Element::SetSprite(sf::Texture* texture)
{
	sprite.setTexture(*texture);
}

sf::Sprite* GUI_Element::GetSprite()
{
	return &sprite;
}
