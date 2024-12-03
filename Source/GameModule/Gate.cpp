#include "GameModule/Gate.hpp"
#include "Common/Logs.hpp"

Gate::Gate(const sf::Vector2i& position, bool isLocked, Key* key) : gatePosition(position), locked(isLocked), associatedKey(key) {}

sf::Vector2i Gate::getGatePosition() const
{
	return gatePosition;
}

bool Gate::isLocked() const
{
	return locked;
}

void Gate::unlock(Key* key)
{
	// If the key is collected, unlock the door
	if (key && (key->isCollected()))
	{
		locked = false;
		LOG("Gate unlocked!");
	}
	else
	{
		LOG("You need to find key first.");
	}
}
