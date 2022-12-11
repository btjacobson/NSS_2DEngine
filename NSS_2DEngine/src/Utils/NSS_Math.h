#ifndef NSS_MATH_H
#define NSS_MATH_H

#include <math.h>

#include <SFML/System/Vector2.hpp>

sf::Vector2f NormalizeVector(sf::Vector2f source)
{
	if (source.x != 0 && source.y != 0)
	{
		source /= sqrt(2.0f);
	}

	return source;
}

#endif
