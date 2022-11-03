#include "Map.h"

Map::Map(sf::Vector2i mapSize, int tileSize)
{
	this->mapSize = mapSize;
	this->tileSize = tileSize;
}

Map::~Map()
{
	for (auto& tile : tiles)
	{
		delete tile;
		tile = nullptr;
	}

	tiles.clear();
}

void Map::BuildMap()
{
	for (int x = 0; x < mapSize.x; ++x)
	{
		for (int y = 0; y < mapSize.y; ++y)
		{
			tiles.push_back(new Tile(sf::Vector2f(x * tileSize, y * tileSize), Asset_Manager::GetInstance()->GetTexture("dirt_tile")));
		}
	}
}

void Map::LoadMapFromFile(std::string filePath)
{

}

void Map::Update(float dt)
{
	for (auto& tile : tiles)
	{
		tile->Update(dt);
	}
}

void Map::Draw(sf::RenderWindow* window)
{
	for (auto& tile : tiles)
	{
		window->draw(*tile->GetSprite());
	}
}
