#pragma once
#include "TestModule/TestBase.hpp"
#include "EventSystem/EventSystem.hpp"
#include <iostream>

class QuestSystemTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime) override { deltaTime = 0.0f; }
	bool isComplete() const override;

private:
	int32_t placeBombEventID, destroyBlockEventID;
	const std::string Name = "QuestSystemTest";
	EventSystem::FunctionHandle handle;
};
