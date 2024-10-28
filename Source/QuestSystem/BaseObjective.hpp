#pragma once
#include <iostream>
#include "EventSystem/EventTypes.hpp"

class BaseObjective {
public:
	BaseObjective(int32_t requiredCnt, int32_t eventId, int32_t eventFinished);
	
	void markCompleted();
	virtual void checkCompletion() = 0;
	virtual void onEvent();

	void setEventId(int32_t id) { eventId = id; }

protected:
	int32_t eventId = -1;
	int32_t eventFinished = -1;
	FunctionHandle eventHandle;

	int32_t requiredCount;
	int32_t currentCount = 0;
	std::string description;
	bool isCompleted = false;
};