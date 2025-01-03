#include "BombUpBooster.hpp"

void BombUpBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.addMaxBombs();
}

bool BombUpBooster::removeEffect(PlayerCharacter&)
{
    return isEffectDone;
}

bool BombUpBooster::shouldRemoveEffect()
{
    return isEffectDone;
}