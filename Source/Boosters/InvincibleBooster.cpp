#include "Boosters/InvincibleBooster.hpp"


int32_t InvincibleBooster::getBoosterID()
{
	return boosterID;
}

void InvincibleBooster::applyEffect(PlayerCharacter& playerCharacter)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool InvincibleBooster::removeEffect(PlayerCharacter& playerCharacter)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool InvincibleBooster::shoulRemoveEffect()
{
	return isEffectDone;
}
