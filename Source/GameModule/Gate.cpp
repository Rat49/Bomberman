#include "GameModule/Gate.hpp"
#include "Common/Logs.hpp"

Gate::Gate(const sf::Vector2i& position, bool isLocked, std::shared_ptr<Key> key) : gatePosition(position), locked(isLocked), associatedKey(key) 
{
    collision.setObjectParent(this);

    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties(sf::Vector2f((float)getPosition().x, (float)getPosition().y), sf::Vector2f(56.0f, 56.0f));

    collisionBoxID = Modules::Physics->registerObject(collisionBox.get());
}

sf::Vector2i Gate::getGatePosition() const
{
	return gatePosition;
}

bool Gate::isLocked() const
{
	return locked;
}

void Gate::unlock(std::shared_ptr<Key> key)
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
