#include "RemoteControlBooster.hpp"

void RemoteControlBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setCanDetonate(true);
    m_isEffectDone = false;
    startTime = std::chrono::high_resolution_clock::now();
}

bool RemoteControlBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    auto now = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float>(now - startTime).count() >= m_duration)
    {
        playerCharacter.setCanDetonate(false);
        m_isEffectDone = true;
    }
    return m_isEffectDone;
}

bool RemoteControlBooster::shouldRemoveEffect()
{
    return m_isEffectDone;
}
