#pragma once
#include "QuestSystem/BaseObjective.hpp"

class DestroyBlocks : public BaseObjective {
public:
	DestroyBlocks(int32_t requiredBlocks, int32_t eventId, int32_t eventFinished);

	void checkCompletion() override;
};