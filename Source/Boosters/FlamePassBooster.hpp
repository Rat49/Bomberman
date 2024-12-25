#pragma once

#include "BoosterComponent.hpp"
#include <chrono>

class FlamePassBooster : public BoosterComponent
{
public:
    int32_t getBoosterID() override;

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

    //if another booster gets picked up just extend the duration of the first one
    void extendEffect();

private:
    int32_t boosterId;

    float duration = 15.f;

    bool isEffectDone = false;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};
