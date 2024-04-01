#ifndef COLLISION_COMP_H
#define COLLISION_COMP_H

#include <SFML/Graphics/Rect.hpp>

#include "Base_Comp.h"

class CollisionComp
{
public:
	CollisionComp(float x, float y, float width, float height);
	~CollisionComp();

private:
	sf::FloatRect _box;
};

#endif
