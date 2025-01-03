#include "RemoteControlBooster.hpp"
#include <Common/Logs.hpp>

void RemoteControlBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setCanDetonate(true);
    m_isEffectDone = false;
    m_startTime    = std::chrono::high_resolution_clock::now();
}

bool RemoteControlBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setCanDetonate(false);
    return m_isEffectDone;
}

bool RemoteControlBooster::shouldRemoveEffect()
{
    auto now       = std::chrono::high_resolution_clock::now();
    m_isEffectDone = std::chrono::duration<float>(now - m_startTime).count() >= m_duration;
    return m_isEffectDone;
}
