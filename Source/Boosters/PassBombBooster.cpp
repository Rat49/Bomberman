#include "PassBombBooster.hpp"

void PassBombBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughBombs(true);
    m_isEffectDone = false;
    m_startTime    = std::chrono::high_resolution_clock::now();
}

bool PassBombBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughBombs(false);
    return m_isEffectDone;
}

bool PassBombBooster::shouldRemoveEffect()
{
    auto now       = std::chrono::high_resolution_clock::now();
    m_isEffectDone = std::chrono::duration<float>(now - m_startTime).count() >= m_duration;
    return m_isEffectDone;
}
