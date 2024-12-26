#include "Boosters/InvincibleBooster.hpp"

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

bool InvincibleBooster::shouldRemoveEffect()
{
	return isEffectDone;
}
