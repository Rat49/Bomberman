#include "ReachNumberObjective.hpp"

ReachNumberObjective::ReachNumberObjective(int32_t requiredCount, int32_t eventId, int32_t eventFinished) : BaseObjective(eventId, eventFinished), requiredCount(requiredCount)
{ 
}

void ReachNumberObjective::checkCompletion()
{
	if (currentCount >= requiredCount) {
		isCompleted = true;
		markCompleted();
	}
}
/*
void ReachNumberObjective::onEvent()
{
	if (currentCount < requiredCount) {
		currentCount++;
	}
	checkCompletion();
}
*/
