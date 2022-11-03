#include "Camera.h"

Camera::Camera() : entity(nullptr)
{
	view.setSize(200, 200);
}

Camera::~Camera()
{
	entity = nullptr;
}

void Camera::Update(float dt)
{
	if (entity)
	{
		view.setCenter(entity->GetPosition());
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
