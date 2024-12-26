#include "FlamePassBooster.hpp"

void FlamePassBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughFlame(true);
    isEffectDone = false;
    startTime = std::chrono::high_resolution_clock::now();
}

bool FlamePassBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughFlame(false);
    return isEffectDone;
}

bool FlamePassBooster::shouldRemoveEffect()
{
    auto now = std::chrono::high_resolution_clock::now();
    isEffectDone = std::chrono::duration<float>(now - startTime).count() >= duration;
    return isEffectDone;
}

void FlamePassBooster::extendEffect()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimeNew =
        std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration<float>(startTimeNew - startTime).count();
}
