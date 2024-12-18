#include "SpeedBooster.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"

namespace
{
const int32_t BOOSTER_ENABLED_STAGE = 4;   // speed booster works only on this stage
const int32_t SPEED_FACTOR = 1.1;          // slightly increasing speed value (10%)
}

void SpeedBooster::applyEffect(PlayerCharacter& playerCharacter)
{
    // If it is expected that game is made so that speed up booster only exists on stage 4, no need for this check 
    if (Modules::Game->getCurrentStage() == BOOSTER_ENABLED_STAGE)
    {
        playerCharacter.updateSpeed(SPEED_FACTOR);
    }
}

bool SpeedBooster::removeEffect(PlayerCharacter& playerCharacter)
{
    playerCharacter.updateSpeed(1.f / SPEED_FACTOR);
    return true;
}

bool SpeedBooster::shouldRemoveEffect()
{
    // If speed booster shouldn't be removed this should just return true
    return Modules::Game->getCurrentStage() > BOOSTER_ENABLED_STAGE;
}
