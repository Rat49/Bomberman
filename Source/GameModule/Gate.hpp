#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameModule/Key.hpp"

class Gate : public sf::Sprite
{
public:
	Gate(const sf::Vector2i& position, bool isLocked = true, std::shared_ptr<Key> key = nullptr);

	sf::Vector2i getGatePosition() const;
	bool isLocked() const;
	void unlock(std::shared_ptr<Key> key);

private:
	sf::Vector2i gatePosition;
	bool locked = true;
	std::shared_ptr<Key> associatedKey;
};
