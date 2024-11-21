#pragma once

#include <SFML/Graphics.hpp>
#include "GameModule/Key.hpp"

class Gate
{
public:
	Gate(const sf::Vector2i& position, bool isLocked = true, Key* key = nullptr);

	sf::Vector2i getGatePosition() const;
	bool isLocked() const;
	void unlock(Key* key);

private:
	sf::Vector2i gatePosition;
	bool locked;
	Key* associatedKey;
};
