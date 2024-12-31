#include "WallPassBooster.hpp"

void WallPassBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughWall(true);
    m_isEffectDone = false;
    m_startTime    = std::chrono::high_resolution_clock::now();
}

bool WallPassBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughWall(false);
    return m_isEffectDone;
}

bool WallPassBooster::shouldRemoveEffect()
{
    auto now       = std::chrono::high_resolution_clock::now();
    m_isEffectDone = std::chrono::duration<float>(now - m_startTime).count() >= m_duration;
    return m_isEffectDone;
}
