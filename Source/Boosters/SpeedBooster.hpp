#pragma once
#include "BoosterComponent.hpp"

class SpeedBooster : public BoosterComponent
{
public:
    int32_t getBoosterID() override { return m_boosterId; }

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

private:
    int32_t m_boosterId;
};