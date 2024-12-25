#pragma once

#include "Boosters/BoosterComponent.hpp"

class InvincibleBooster : public BoosterComponent
{
public:
	int32_t getBoosterID() override;


	void applyEffect(PlayerCharacter& playerCharacter) override;


	bool removeEffect(PlayerCharacter& playerCharacter) override;


	bool shouldRemoveEffect() override;

private:
	int32_t boosterID = 1;
	bool isEffectDone = false;

};
