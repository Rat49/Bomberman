#pragma once
#include "BaseObjective.hpp"

class ReachNumberObjective : public BaseObjective {
public:
	ReachNumberObjective(int32_t requiredCount, int32_t eventId, int32_t eventFinished);
	void checkCompletion() override;

protected:
	int32_t requiredCount;
	int32_t currentCount = 0;
};