#include "GameModule/Key.hpp"

Key::Key(const sf::Vector2i& position) : keyPosition(position), collected(false) {}

sf::Vector2i Key::getKeyPosition() const
{
	return keyPosition;
}

bool Key::isCollected() const
{
	return collected;
}

// Method indicating that the key has been collected
void Key::collect()
{
	collected = true;
}
