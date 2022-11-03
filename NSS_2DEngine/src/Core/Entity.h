#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(sf::Vector2f position, sf::Texture* texture);
	~Entity();

	void Update(float dt);
	void SetVelocity(float vel);

	sf::Sprite* GetSprite();
	sf::Vector2f GetPosition();

private:
	sf::Sprite sprite;

	float velocity;
};

#endif
