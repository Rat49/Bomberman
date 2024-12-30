#include "SpeedBooster.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"

namespace
{
    const int32_t BOOSTER_ENABLED_STAGE = 4;   // speed booster works only on this stage
    const float SPEED_FACTOR = 1.1f;          // slightly increasing speed value (10%)
}

void SpeedBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    // If it is expected that game is made so that speed up booster only exists on stage 4, no need for this check 
    if (Modules::Game->getCurrentStage() == BOOSTER_ENABLED_STAGE)
    {
        playerCharacter.setNewSpeed(SPEED_FACTOR);
        m_isEffectDone = false;
        m_startTime    = std::chrono::high_resolution_clock::now();
    }
}

bool SpeedBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.setNewSpeed(1.f / SPEED_FACTOR);
    return m_isEffectDone;
}

bool SpeedBooster::shouldRemoveEffect()
{
    // If speed booster shouldn't be removed this should just return true
    if (Modules::Game->getCurrentStage() == BOOSTER_ENABLED_STAGE)
    {
        auto now       = std::chrono::high_resolution_clock::now();
        m_isEffectDone = std::chrono::duration<float>(now - m_startTime).count() >= m_duration;
    }
    return m_isEffectDone;
}
