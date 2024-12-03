#include "GameModule/Booster.hpp"
#include <iostream>

Booster::Booster(BoosterType type) : type(type) {}

sf::Vector2i Booster::getPosition() const
{
	return boosterPosition;
}

// A function that returns the name of the booster type as a string
std::string Booster::getTypeAsString() const
{
	switch (type)
	{
	case BoosterType::Speed: return "speed";
	case BoosterType::Bomb: return "bomb";
	case BoosterType::Health: return "health";
	default: return "unknown";
	}
}

// A function that applies a booster effect
void Booster::applyEffect()
{
	switch (type)
	{
	case BoosterType::Speed:
		std::cout << "Speed boost applied!" << std::endl;
		break;
	case BoosterType::Bomb:
		std::cout << "Bomb boost applied!" << std::endl;
		break;
	case BoosterType::Health:
		std::cout << "Health boost applied!" << std::endl;
		break;
	default:
		std::cout << "Unknown boost!" << std::endl;
		break;
	}
}
