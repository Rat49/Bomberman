#pragma once

#include "BoosterComponent.hpp"

class FireUpBooster : public BoosterComponent
{
public:

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

private:
    bool    isEffectDone = false;
};