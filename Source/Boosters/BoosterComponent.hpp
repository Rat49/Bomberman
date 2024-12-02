#pragma once
#include "GameModule/PlayerCharacter.hpp"

class BoosterComponent
{
public:
	virtual int32_t getBoosterID() = 0;
	virtual void applyEffect(PlayerCharacter& playerCharacter) = 0;
	virtual bool removeEffect(PlayerCharacter& playerCharacter) = 0;
	virtual bool shoulRemoveEffect() = 0;
};