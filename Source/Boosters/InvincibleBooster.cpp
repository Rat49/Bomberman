#include "Boosters/InvincibleBooster.hpp"


int32_t InvincibleBooster::getBoosterID()
{
	return boosterID;
}

void InvincibleBooster::applyEffect(PlayerCharacter& playerCharacter)
{
	playerCharacter.startInvincibility();
	isEffectDone = false;
}

bool InvincibleBooster::removeEffect(PlayerCharacter& playerCharacter)
{
	playerCharacter.updateInvincibility();
	if (!playerCharacter.getIsInvincible())
	{
		isEffectDone = true;
	}
	return isEffectDone;
}

bool InvincibleBooster::shoulRemoveEffect()
{
	return isEffectDone;
}
