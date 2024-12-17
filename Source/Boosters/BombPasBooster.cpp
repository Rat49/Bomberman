#include "BombPasBooster.hpp"

int32_t BombPasBooster::getBoosterID()
{
    return m_boosterId;
}

void BombPasBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.startPassThroughBombs();
    m_isEffectDone = false;
    startTime      = std::chrono::high_resolution_clock::now();
}

bool BombPasBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    auto now = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float>(now - startTime).count() >= m_duration)
    {
        playerCharacter.stopPassThroughBombs();
        m_isEffectDone = true;
    }
    return m_isEffectDone;
}

bool BombPasBooster::shoulRemoveEffect()
{
    return m_isEffectDone;
}
