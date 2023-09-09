#include "Map.h"

Map::Map(sf::Vector2i mapSize, int tileSize)
{
	this->mapSize = mapSize;
	this->tileSize = tileSize;

	LoadTextures();
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
			if ((x == 0 || y == 0) || (x == mapSize.x - 1 || y == mapSize.y - 1))
			{
				tiles.push_back(new Tile(sf::Vector2f(x * tileSize, y * tileSize), Asset_Manager::GetInstance()->GetTexture("water_tile"), true));
			}
			else 
			{
				tiles.push_back(new Tile(sf::Vector2f(x * tileSize, y * tileSize), Asset_Manager::GetInstance()->GetTexture("dirt_tile")));
			}
		}
	}
}

void Map::LoadTextures()
{
	Asset_Manager::GetInstance()->AddTexture("dirt_tile", "../assets/textures/tiles/dirt_tile.png");
	Asset_Manager::GetInstance()->AddTexture("water_tile", "../assets/textures/tiles/water_tile.png");
	Asset_Manager::GetInstance()->AddTexture("grass_tile", "../assets/textures/tiles/grass_tile.png");
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

bool Map::GetCollisionForTile(int x, int y)
{
	bool found = false;
	for (auto& tile : tiles)
	{
		sf::IntRect tileRect = tile->GetSprite()->getTextureRect();
		tileRect.left += tile->GetSprite()->getPosition().x;
		tileRect.top += tile->GetSprite()->getPosition().y;

		if (tileRect.contains(x, y))
		{
			found = tile->GetCollisionEnabled();
		}
	}

	return found;
}
