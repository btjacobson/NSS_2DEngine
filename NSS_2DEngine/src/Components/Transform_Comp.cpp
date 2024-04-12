#include "Transform_Comp.h"

#include <iostream>
#include <math.h>

TransformComp::TransformComp(float posX, float posY)
{
	_position = sf::Vector2f(posX, posY);
	_rotation = 0.0f;
	_scale = sf::Vector2f(0, 0);
}

TransformComp::~TransformComp()
{

}

void TransformComp::SetPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

void TransformComp::SetPosition(sf::Vector2f position)
{
	_position = position;
}

void TransformComp::SetRotation(float rotation)
{
	_rotation = rotation;
}

void TransformComp::SetScale(float x, float y)
{
	_scale.x = x;
	_scale.y = y;
}

void TransformComp::SetScale(sf::Vector2f scale)
{
	_scale = scale;
}

void TransformComp::Move(sf::Vector2f value)
{
	_position.x += value.x;
	_position.y += value.y;
}

sf::Vector2f TransformComp::GetPosition()
{
	return _position;
}

float TransformComp::GetRotation()
{
	return _rotation;
}

sf::Vector2f TransformComp::GetScale()
{
	return _scale;
}
