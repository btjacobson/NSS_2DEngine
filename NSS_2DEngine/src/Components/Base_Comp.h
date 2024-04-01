#ifndef BASE_COMP_H
#define BASE_COMP_H

#include <random>

class BaseComp
{
public:
	BaseComp(class Entity* owner)
	{
		_id = std::rand() % (999999 - 100000 + 1) + 100000;
		_owner = owner;
	}

	inline int GetId()
	{
		return _id;
	}

protected:
	int _id;
	class Entity* _owner;
};

#endif
