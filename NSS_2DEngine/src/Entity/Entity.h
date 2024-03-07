#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	void AddComponent(Component*);
	void RemoveComponent();
	void Update(float dt);

protected:

};

#endif
