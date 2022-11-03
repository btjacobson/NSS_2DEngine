#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

class Tile
{
public:
	Tile(sf::Vector2f position, sf::Texture* texture, bool collision = false);
	~Tile();

	void Update(float dt);
	void ToggleCollision();

	bool GetCollisionEnabled();
	sf::Sprite* GetSprite();

private:
	sf::Sprite sprite;

	bool collisionEnabled;
};

#endif
