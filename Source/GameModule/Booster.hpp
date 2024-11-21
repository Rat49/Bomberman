#pragma once

#include <string>

enum class BoosterType
{
	Speed,
	Bomb,
	Health
};

class Booster
{
public:
	Booster(BoosterType type);

	// A function that returns the name of the booster type as a string
	std::string getTypeAsString() const;

	// A function that applies a booster effect
	void applyEffect();

private:
	BoosterType type;
};
