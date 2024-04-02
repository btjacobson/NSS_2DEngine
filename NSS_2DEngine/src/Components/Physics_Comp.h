#ifndef PHYSICS_COMP_H
#define PHYSICS_COMP_H

#include <SFML/Graphics/Transform.hpp>

#include "Base_Comp.h"
#include "Transform_Comp.h"

class PhysicsComp : public BaseComp
{
public:
	PhysicsComp(float maxVelocity, float acceleration);
	~PhysicsComp();

	void Update(float dt) override;

private:
	sf::Vector2f _acceleration;
	sf::Vector2f _maxVelocity;
	sf::Vector2f _velocity;

};

#endif
