#include "DestroyBlocks.hpp"
#include "QuestSystem/BaseObjective.hpp"

DestroyBlocks::DestroyBlocks(int32_t requiredBlocks, int32_t eventId, int32_t eventFinished) : BaseObjective(requiredBlocks, eventId, eventFinished)
{}

void DestroyBlocks::checkCompletion()
{
	if (currentCount >= requiredCount) {
		isCompleted = true;
		markCompleted();
	}
}
