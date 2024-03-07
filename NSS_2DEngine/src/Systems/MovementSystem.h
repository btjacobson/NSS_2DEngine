#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../Entity/Entity.h"

#include "../Components/Transform_Comp.h"

#include <unordered_map>
#include <string>

class MovementSystem
{
public:
	static MovementSystem* GetInstance();

	~MovementSystem();

	void Update(std::unordered_map<std::string, Entity*> entities)
	{
		for (const auto& entity : entities)
		{
			if (auto position = entity.second->GetComponent<TransformComp>())
			{

			}
		}
	}

private:
	MovementSystem() = default;
	MovementSystem(MovementSystem&) {}
	void operator=(MovementSystem const&) const {}

	static MovementSystem* instance;
};

#endif
