#ifndef CAMERA_H
#define CAMERA_H

#include "SFML/Graphics.hpp"

#include "../Entity/Entity.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Update(float dt);
	void Draw(sf::RenderWindow* window);
	void FollowTarget(Entity* entity);
	void StopFollowingTarget();

private:
	sf::View view;

	Entity* entity;
};

#endif
