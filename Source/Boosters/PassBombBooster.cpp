#include "PassBombBooster.hpp"

int32_t PassBombBooster::getBoosterID()
{
    return m_boosterId;
}

void PassBombBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.PassThroughBombs(true);
    m_isEffectDone = false;
    startTime      = std::chrono::high_resolution_clock::now();
}

bool PassBombBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    auto now = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float>(now - startTime).count() >= m_duration)
    {
        playerCharacter.PassThroughBombs(false);
        m_isEffectDone = true;
    }
    return m_isEffectDone;
}

bool PassBombBooster::shoulRemoveEffect()
{
    return m_isEffectDone;
}
