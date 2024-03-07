#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "../Entity/Entity.h"

class Entity_Manager
{
public:
	static Entity_Manager* GetInstance();

	~Entity_Manager();
	
	template<class T>
	void AddEntity(std::string name)
	{
		T* tEntity = new T();

		if (tEntity && entities.find(name) == entities.end())
		{
			entities.insert(std::make_pair(name, tEntity));
		}
	}

	void RemoveEntity(std::string name);
	void ClearEntities();
	void Update(float dt);
	void Draw(sf::RenderWindow* window);

	Entity* GetEntity(std::string name);
	std::unordered_map<std::string, Entity*>* GetEntities();

private:
	Entity_Manager() = default;
	Entity_Manager(Entity_Manager&) {}
	void operator=(Entity_Manager const&) const {}

	static Entity_Manager* instance;

	std::unordered_map<std::string, Entity*> entities;
};

#endif
