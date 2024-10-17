#pragma once
#include <iostream>

class BaseObjective {
public:
	BaseObjective(int32_t requiredCnt) : requiredCount(requiredCnt) {}

	virtual void checkCompletion();
	virtual void onEvent();

protected:
	int32_t requiredCount;
	int32_t currentCount = 0;
	std::string description;
	bool isCompleted = false;
};