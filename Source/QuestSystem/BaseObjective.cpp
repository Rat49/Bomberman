#include "BaseObjective.hpp"

void BaseObjective::checkCompletion()
{
	if (currentCount >= requiredCount) {
		isCompleted = true;
	}
}

void BaseObjective::onEvent()
{
	if (currentCount < requiredCount) {
		currentCount++;
		//update state
	}
	checkCompletion();
}
