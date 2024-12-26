#include "QuestSystem/FailObjective.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

FailObjective::FailObjective(int32_t eventId, int32_t eventFailed) : BaseObjective(eventId, eventFailed) { }

void FailObjective::checkCompletion()
{
    if (isFailed)
    {
        // Emit fail event
        Modules::Events->emit(eventFinished, nullptr);
    }
}

void FailObjective::onEvent()
{
    isFailed = true;
    checkCompletion();
}
