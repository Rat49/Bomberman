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

float FloatUtils::squareDistance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
	float dx = point2.x - point1.x;
	float dy = point2.y - point1.y;
	return (dx * dx + dy * dy);
}