#pragma once
#include "GameModule/PlayerCharacter.hpp"

class BoosterComponent
{
public:
	virtual void applyEffect(PlayerCharacter& playerCharacter) = 0;
	virtual bool removeEffect(PlayerCharacter& playerCharacter) = 0;
	virtual bool shouldRemoveEffect() = 0;
};