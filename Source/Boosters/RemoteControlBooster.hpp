#pragma once
#include "BoosterComponent.hpp"
#include <chrono>

class RemoteControlBooster : public BoosterComponent
{
public:

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

private:

    float m_duration = 10.f;

    bool m_isEffectDone;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};