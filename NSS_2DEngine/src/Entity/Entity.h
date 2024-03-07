#ifndef ENTITY_H
#define ENTITY_H

#include "../Components/Base_Comp.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Entity
{
public:
	Entity();
	~Entity();

	void AddComponent(BaseComp* component);

	template<typename T>
	void RemoveComponent()
	{
		for (const auto& component : _components)
		{
			if (T* found = static_cast<T*>(component))
			{
				_components.erase(found);
				break;
			}
		}
	}

	template<typename T>
	T* GetComponent()
	{
		for (const auto& component : _components)
		{
			if (T* found = static_cast<T*>(component))
			{
				return found;
			}
		}

		return nullptr;
	}

protected:
	std::vector<BaseComp*> _components;
};

#endif
