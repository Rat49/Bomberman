#include "BaseObjective.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

BaseObjective::BaseObjective(int32_t requiredCount, int32_t eventId, int32_t eventFinished) : requiredCount(requiredCount), eventId(eventId), eventFinished(eventFinished) 
{
	eventHandle = Modules::Events->subscribe(eventId, std::bind(&BaseObjective::onEvent, this));
}

void BaseObjective::markCompleted()
{
	isCompleted = true;
	Modules::Events->emit(eventFinished, nullptr);
}

void BaseObjective::onEvent()
{
	if (currentCount < requiredCount) {
		currentCount++;
	}
	checkCompletion();
}
