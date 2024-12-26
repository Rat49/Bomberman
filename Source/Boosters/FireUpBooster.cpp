#include "FireUpBooster.hpp"

void FireUpBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.addExplosionRadius();
}

bool FireUpBooster::removeEffect(PlayerCharacter&)
{
    return isEffectDone;
}

bool FireUpBooster::shouldRemoveEffect()
{
    return isEffectDone;
}