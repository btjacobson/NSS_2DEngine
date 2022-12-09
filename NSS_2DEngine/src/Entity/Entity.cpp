#include "Entity.h"

Entity::Entity(sf::Vector2f position, sf::Texture* texture)
{
    sprite.setPosition(position);
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    velocity = sf::Vector2f();
}

Entity::~Entity()
{

}

void Entity::Update(float dt)
{
    sprite.move(velocity);
}

sf::Sprite* Entity::GetSprite()
{
    return &sprite;
}

sf::Vector2f Entity::GetPosition()
{
    return sprite.getPosition();
}
