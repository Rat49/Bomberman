#include "FloatUtils.hpp"
#include <limits>
#include <cmath>

bool FloatUtils::isAlmostZero(float x) 
{
	return std::fabs(x) < std::numeric_limits<float>::epsilon();
}

bool FloatUtils::isAlmostZero(sf::Vector2f vec)
{
	return isAlmostZero(vec.x) && isAlmostZero(vec.y);
}