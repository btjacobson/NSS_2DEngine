#include "Transform_Comp.h"

#include <iostream>

TransformComp::TransformComp(float posX, float posY)
{
}

TransformComp::~TransformComp()
{
}

void TransformComp::SetPosition(float x, float y)
{
}

void TransformComp::SetPosition(sf::Vector2f position)
{
}

void TransformComp::SetRotation(float rotation)
{
}

void TransformComp::SetScale(float x, float y)
{
}

void TransformComp::SetScale(sf::Vector2f scale)
{
}

void TransformComp::Move(sf::Vector2f movement, float deltaTime)
{
	_position.x += movement.x * deltaTime;
	_position.y += movement.y * deltaTime;

	std::cout << _position.x << ", " << _position.y << std::endl;
}

sf::Vector2f TransformComp::GetPosition()
{
	return sf::Vector2f();
}

float TransformComp::GetRotation()
{
	return 0.0f;
}

sf::Vector2f TransformComp::GetScale()
{
	return sf::Vector2f();
}
