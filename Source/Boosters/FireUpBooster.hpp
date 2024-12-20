#pragma once

#include "BoosterComponent.hpp"

class FireUpBooster : public BoosterComponent
{
public:
    int32_t getBoosterID() override;

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

private:
    int32_t boosterId;
    bool    isEffectDone = false;
};