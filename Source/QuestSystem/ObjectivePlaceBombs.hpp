#pragma once
#include "BaseObjective.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

class ObjectivePlaceBombs : public BaseObjective {
public:
	ObjectivePlaceBombs(int32_t requiredBombs) : BaseObjective(requiredBombs) {
		//bombPlacedHandle = Modules::Events->subscribe<void>(bombPlacedID, std::bind(&ObjectivePlaceBombs::onEvent, this));
	}

	~ObjectivePlaceBombs() {
		Modules::Events->unsubscribe(bombPlacedID, bombPlacedHandle);
	}

	void setBombPlacedId(int32_t bombID);
private:
	int32_t bombPlacedID;
	EventSystem::FunctionHandle bombPlacedHandle;
};