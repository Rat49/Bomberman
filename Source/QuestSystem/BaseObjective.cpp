#include "BaseObjective.hpp"
#include "Common/Modules.hpp"

BaseObjective::BaseObjective(int32_t requiredCnt, int32_t eventId, int32_t eventFinished) : requiredCount(requiredCnt), eventId(eventId), eventFinished(eventFinished) 
{
	eventHandle = Modules::Events->subscribe(eventId, std::bind(&BaseObjective::onEvent, this));
}

void BaseObjective::markCompleted()
{
	Modules::Events->emit(eventFinished, nullptr);
}

void BaseObjective::checkCompletion()
{
	if (currentCount >= requiredCount) {
		isCompleted = true;
		markCompleted();
	}
}

void BaseObjective::onEvent()
{
	if (currentCount < requiredCount) {
		currentCount++;
	}
	checkCompletion();
}
