#pragma once
#include "CollisionModule/CollisionObject.hpp"
#include "Boosters/BoosterComponent.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

enum class BoosterType
{
	Speed,
	PassBomb,
	FireUp,
	BombUp,
	RemoteControl,
	InvincibleBooster,
	FlamePass,
	WallPass,
	MaxValue
};

class Booster : public sf::Sprite, public CollisionObject
{
public:
	Booster(BoosterType type, float x, float y);

	// A function that returns the name of the booster type as a string
	std::string getTypeAsString() const;

	std::shared_ptr<BoosterComponent> getBoosterComponent();

	bool getIsPickedUp() const { return isPickedUp; }

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

private:
    std::unique_ptr<CollisionComponent> collisionBox;

	BoosterType type;
	sf::Vector2f boosterPosition;

	bool isPickedUp = false;
};
