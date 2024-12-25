#pragma once
#include "GameModule/PlayerCharacter.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

class BoosterComponent
{
public:
	virtual int32_t getBoosterID() = 0;

	virtual void applyEffect(PlayerCharacter& playerCharacter) = 0;

	virtual bool removeEffect(PlayerCharacter& playerCharacter) = 0;

	virtual bool shouldRemoveEffect() = 0;

	void setCallback(EventID callbackID)
	{
        m_pickupID = callbackID;
	}

	void emitCallback() const
	{
        Modules::Events->emit(m_pickupID, nullptr);
	}

protected:
    EventID m_pickupID = -1;

};