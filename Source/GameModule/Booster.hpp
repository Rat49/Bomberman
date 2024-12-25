#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "EventSystem/EventTypes.hpp"

enum class BoosterType
{
	Speed,
	Bomb,
	Health,
	PassBomb
};

class Booster : public sf::Sprite
{
public:
	Booster(BoosterType type);

	sf::Vector2i getPosition() const;

	// A function that returns the name of the booster type as a string
	std::string getTypeAsString() const;

	// A function that applies a booster effect
	void applyEffect();

	void setCallbackID(EventID boosterPickupID);

private:
	BoosterType type;
	sf::Vector2i boosterPosition;
	EventID m_boosterPickupID = -1;
};
