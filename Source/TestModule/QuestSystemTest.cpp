#include "TestModule/QuestSystemTest.hpp"
#include "Common/Modules.hpp"
#include "QuestSystem/QuestSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

const std::string& QuestSystemTest::getName() const
{
	return Name;
}

void QuestSystemTest::setup()
{
	LOG("QuestSystemTest: setup()");

	Modules::Quests->addQuests("../../Data/Config/questSystem.ini");
}

void QuestSystemTest::run()
{
	LOG("QuestSystemTest: run()");

	Modules::Quests->startQuest(0);
	Modules::Quests->emitMyEvent(EventType::PlaceBombs);
	Modules::Quests->emitMyEvent(EventType::DestroyBlocks);
}

bool QuestSystemTest::isComplete() const
{
	return true;
}
