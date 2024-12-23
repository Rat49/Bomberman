#pragma once
#include <functional>

using EventID        = int32_t;
using FunctionHandle = int32_t;
using Callback       = std::function<void(void*)>;

namespace EventTypes
{
extern EventID GAME_TIMER_FINISHED;
extern EventID QUEST_FAILED;
extern EventID PLAYER_DESTROYED;
extern EventID OBJECTIVE_COMPLETED;

void initialize();
} // namespace EventTypes