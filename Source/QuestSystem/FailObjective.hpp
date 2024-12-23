#pragma once

#include "QuestSystem/BaseObjective.hpp"

class FailObjective : public BaseObjective
{
public:
    FailObjective(int32_t eventId, int32_t eventFailed);

    void checkCompletion() override;
    void onEvent() override;

private:
    bool isFailed = false;
};