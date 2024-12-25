#pragma once
#include <SFML/Graphics.hpp>
class FloatUtils
{
public:
	static bool isAlmostZero(float x);

	static bool isAlmostZero(sf::Vector2f vec);

	static float squareDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);

	static bool areVectorsEqual(const sf::Vector2f& v1, const sf::Vector2f& v2);
};

