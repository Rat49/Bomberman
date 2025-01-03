#pragma once
#include "EventSystem/EventTypes.hpp"
#include <iostream>

class BaseObjective
{
public:
    BaseObjective(int32_t eventId, int32_t eventFinished);

    void         markCompleted();
    virtual void checkCompletion() = 0;
    virtual void onEvent()         = 0;

    void setEventId(int32_t id)
    {
        eventId = id;
    }

protected:
    int32_t        eventId       = -1;
    int32_t        eventFinished = -1;
    FunctionHandle eventHandle;

    std::string description;
    bool        isCompleted = false;
};