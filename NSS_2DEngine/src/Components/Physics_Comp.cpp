#include "Physics_Comp.h"

#include "../Entity/Entity.h"

PhysicsComp::PhysicsComp(float maxVelocity, float acceleration)
{
	_acceleration.x = acceleration;
	_acceleration.y = acceleration;

	_maxVelocity.x = maxVelocity;
	_maxVelocity.y = maxVelocity;

	_velocity = sf::Vector2f(0, 0);
}

PhysicsComp::~PhysicsComp()
{

}

void PhysicsComp::Update(float dt)
{
	_velocity += _acceleration;

	if (_velocity.x > _maxVelocity.x)
	{
		_velocity.x = _maxVelocity.x;
	}

	if (_velocity.y > _maxVelocity.y)
	{
		_velocity.y = _maxVelocity.y;
	}

	_owner->GetComponent<TransformComp>()->Move(_velocity *= dt);
}
