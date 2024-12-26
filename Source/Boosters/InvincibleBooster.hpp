#pragma once

#include "Boosters/BoosterComponent.hpp"

class InvincibleBooster : public BoosterComponent
{
public:

	void applyEffect(PlayerCharacter& playerCharacter) override;


	bool removeEffect(PlayerCharacter& playerCharacter) override;


	bool shouldRemoveEffect() override;

private:
	bool isEffectDone = false;

};
