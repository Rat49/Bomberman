#include "EventSystem/EventTypes.hpp"
#include "EventSystem/EventSystem.hpp"
#include "Common/Modules.hpp"

EventID EventTypes::GAME_TIMER_FINISHED;
EventID EventTypes::QUEST_FAILED;
EventID EventTypes::PLAYER_DESTROYED;
EventID EventTypes::OBJECTIVE_COMPLETED;

void EventTypes::initialize()
{
    GAME_TIMER_FINISHED = Modules::Events->registerEvent();
    QUEST_FAILED        = Modules::Events->registerEvent();
    PLAYER_DESTROYED    = Modules::Events->registerEvent();
    OBJECTIVE_COMPLETED = Modules::Events->registerEvent();
}