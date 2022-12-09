#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(sf::Vector2f position, sf::Texture* texture);
	~Entity();

	void Update(float dt);
	virtual void SetVelocity(sf::Vector2f vel) = 0;

	sf::Sprite* GetSprite();
	sf::Vector2f GetPosition();

protected:
	sf::Sprite sprite;

	sf::Vector2f velocity;
};

#endif
