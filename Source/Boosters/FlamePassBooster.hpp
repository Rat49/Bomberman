#pragma once

#include "BoosterComponent.hpp"
#include <chrono>

class FlamePassBooster : public BoosterComponent
{
public:

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

    //if another booster gets picked up just extend the duration of the first one
    void extendEffect();

private:

    float m_duration = 20.f;

    bool m_isEffectDone = false;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};
