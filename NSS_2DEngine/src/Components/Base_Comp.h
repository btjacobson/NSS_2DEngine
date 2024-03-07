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

private:
	int _id;
};

#endif
