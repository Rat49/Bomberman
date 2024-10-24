#pragma once
#include <SFML/Graphics.hpp>
class FloatUtils
{
public:
	static bool isAlmostZero(float x);

	static bool isAlmostZero(sf::Vector2f vec);
};

