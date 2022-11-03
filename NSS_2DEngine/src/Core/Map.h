#ifndef MAP_H
#define MAP_H

#include <vector>

#include "../Managers/Asset_Manager.h"
#include "Tile.h"

class Map
{
public:
	Map(sf::Vector2i mapSize, int tileSize);
	~Map();

	void BuildMap();
	void LoadMapFromFile(std::string filePath);
	void Update(float dt);
	void Draw(sf::RenderWindow* window);

private:
	sf::Vector2i mapSize;
	std::vector<Tile*> tiles;
	int tileSize;
};

#endif