#include "Boosters/InvincibleBooster.hpp"

void InvincibleBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setInvincibility(true);
    m_isEffectDone = false;
    m_startTime    = std::chrono::high_resolution_clock::now();
}

bool InvincibleBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setInvincibility(false);
    return m_isEffectDone;
}

bool InvincibleBooster::shouldRemoveEffect()
{
    auto now       = std::chrono::high_resolution_clock::now();
    m_isEffectDone = std::chrono::duration<float>(now - m_startTime).count() >= m_duration;
    return m_isEffectDone;
}
