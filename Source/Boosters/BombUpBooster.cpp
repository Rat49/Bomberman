#include "BombUpBooster.hpp"

int32_t BombUpBooster::getBoosterID()
{
    return boosterId;
}

void BombUpBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.addMaxBombs();
}

bool BombUpBooster::removeEffect(PlayerCharacter& )
{
    return isEffectDone;
}

bool BombUpBooster::shouldRemoveEffect()
{
    return isEffectDone;
}