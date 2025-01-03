#include "BaseObjective.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

BaseObjective::BaseObjective(int32_t eventId, int32_t eventFinished) : eventId(eventId), eventFinished(eventFinished)
{
    eventHandle = Modules::Events->subscribe(eventId, std::bind(&BaseObjective::onEvent, this));
}

void BaseObjective::markCompleted()
{
    isCompleted = true;
    Modules::Events->emit(eventFinished, nullptr);
}