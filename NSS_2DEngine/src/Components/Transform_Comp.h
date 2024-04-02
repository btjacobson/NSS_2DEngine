#ifndef TRANSFORM_COMP_H
#define TRANSFORM_COMP_H

#include <SFML/Graphics/Transform.hpp>

#include "Base_Comp.h"

class TransformComp : public BaseComp
{
public:
	TransformComp(float posX, float posY);
	~TransformComp();

	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);
	void SetRotation(float rotation);
	void SetScale(float x, float y);
	void SetScale(sf::Vector2f scale);
	void Move(sf::Vector2f value);

	sf::Vector2f GetPosition();
	float GetRotation();
	sf::Vector2f GetScale();

private:
	sf::Vector2f _position;
	float _rotation;
	sf::Vector2f _scale;
};

#endif
