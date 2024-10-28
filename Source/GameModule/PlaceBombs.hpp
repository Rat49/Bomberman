#pragma once
#include "QuestSystem/BaseObjective.hpp"

class PlaceBombs : public BaseObjective {
public:
	PlaceBombs(int32_t requiredBombs, int32_t eventId, int32_t eventFinished);
	
	void onEvent() override;

	void checkCompletion() override;
};