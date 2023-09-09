#include "Tile.h"

Tile::Tile(sf::Vector2f position, sf::Texture* texture, bool collision)
{
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    collisionEnabled = collision;
}

Tile::~Tile()
{

}

void Tile::Update(float dt)
{

}

void Tile::ToggleCollision()
{
    collisionEnabled = !collisionEnabled;
}

bool Tile::GetCollisionEnabled()
{
    return collisionEnabled;
}

sf::Sprite* Tile::GetSprite()
{
    return &sprite;
}
