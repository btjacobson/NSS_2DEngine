#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "../Core/Entity.h"

class Entity_Manager
{
public:

	static Entity_Manager* GetInstance();

	~Entity_Manager();

	void AddEntity(std::string name, sf::Vector2f position, sf::Texture* texture);
	void RemoveEntity(std::string name);
	void ClearEntities();
	void Update(float dt);
	void Draw(sf::RenderWindow* window);

	Entity* GetEntity(std::string name);

private:
	Entity_Manager() = default;
	Entity_Manager(Entity_Manager&) {}
	void operator=(Entity_Manager const&) const {}

	static Entity_Manager* instance;

	std::unordered_map<std::string, Entity*> entities;
};

#endif
