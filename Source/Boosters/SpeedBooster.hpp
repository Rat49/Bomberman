#pragma once
#include "BoosterComponent.hpp"

class SpeedBooster : public BoosterComponent
{
public:

    void applyEffect(PlayerCharacter& playerCharacter) override;

    bool removeEffect(PlayerCharacter& playerCharacter) override;

    bool shouldRemoveEffect() override;

private:

    bool m_isEffectDone;
};