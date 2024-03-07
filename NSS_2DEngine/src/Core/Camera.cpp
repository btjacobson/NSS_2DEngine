#include "Camera.h"

Camera::Camera() : entity(nullptr)
{
	view.setSize(480, 270);
}

Camera::~Camera()
{
	entity = nullptr;
}

void Camera::Update(float dt)
{
	if (entity)
	{

	}
}

void Camera::Draw(sf::RenderWindow* window)
{
	window->setView(view);
}

void Camera::FollowTarget(Entity* entity)
{
	this->entity = entity;
}

void Camera::StopFollowingTarget()
{
	entity = nullptr;
}
