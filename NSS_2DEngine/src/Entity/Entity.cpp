#include "Entity.h"

#include "../Utils/NSS_Math.h"

Entity::Entity()
{

}

Entity::~Entity()
{
	for (auto component : _components)
	{
		delete component;
	}

	_components.clear();
}

void Entity::AddComponent(BaseComp* component)
{
	component->SetOwner(this);
	_components.push_back(component);
}
