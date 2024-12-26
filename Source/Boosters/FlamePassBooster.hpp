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

    float duration = 15.f;

    bool isEffectDone = false;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};
