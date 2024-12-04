#pragma once

#include <SFML/Graphics.hpp>

class Key : public sf::Sprite
{
public:
	Key(const sf::Vector2i& position);

	sf::Vector2i getKeyPosition() const;

	// Check if the key has been collected
	bool isCollected() const;

	// Method indicating that the key has been collected
	void collect();

private:
	sf::Vector2i keyPosition;
	bool collected;
};
