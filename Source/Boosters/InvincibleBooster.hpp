#pragma once

#include "Boosters/BoosterComponent.hpp"

class InvincibleBooster : BoosterComponent
{
public:
	int32_t getBoosterID() override;


	void applyEffect(PlayerCharacter& playerCharacter) override;


	bool removeEffect(PlayerCharacter& playerCharacter) override;


	bool shoulRemoveEffect() override;

private:
	int32_t boosterID = 1;
	bool isEffectDone = false;

};
