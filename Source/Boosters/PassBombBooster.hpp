#pragma once
#include "BoosterComponent.hpp"
#include <chrono>

class PassBombBooster : public BoosterComponent
{
public:

    int32_t getBoosterID() override;

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shoulRemoveEffect() override;

private:

    int32_t m_boosterId;

    float m_duration = 10.f;
    
    bool m_isEffectDone;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};
