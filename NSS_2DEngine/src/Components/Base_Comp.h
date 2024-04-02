#ifndef BASE_COMP_H
#define BASE_COMP_H

#include <random>

class BaseComp
{
public:
	BaseComp()
	{
		_id = std::rand() % (999999 - 100000 + 1) + 100000;
	}

	inline int GetId()
	{
		return _id;
	}

	virtual void SetOwner(class Entity* owner)
	{
		_owner = owner;
	}

	virtual void Update(float dt) { }

protected:
	int _id;
	class Entity* _owner;
};

#endif
