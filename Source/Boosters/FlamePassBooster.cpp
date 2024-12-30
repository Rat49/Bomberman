#include "FlamePassBooster.hpp"
#include <Common/Logs.hpp>

void FlamePassBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughFlame(true);
    m_isEffectDone = false;
    m_startTime = std::chrono::high_resolution_clock::now();
}

bool FlamePassBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setPassThroughFlame(false);
    return m_isEffectDone;
}

bool FlamePassBooster::shouldRemoveEffect()
{
    auto now = std::chrono::high_resolution_clock::now();
    m_isEffectDone = std::chrono::duration<float>(now - m_startTime).count() >= m_duration;
    return m_isEffectDone;
}

void FlamePassBooster::extendEffect()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimeNew =
        std::chrono::high_resolution_clock::now();
    m_duration += std::chrono::duration<float>(startTimeNew - m_startTime).count();
}
