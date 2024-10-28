#include "TestModule/QuestSystemTest.hpp"
#include "Common/Modules.hpp"
#include "QuestSystem/QuestSystem.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

const std::string& QuestSystemTest::getName() const
{
	return Name;
}

void QuestSystemTest::setup()
{
	LOG("QuestSystemTest: setup()");
	/*const std::string pathQuestSystem = "../../Data/Config/questSystem.ini";
	Modules::Config->addFile(pathQuestSystem);
	Modules::Quests->addQuests(pathQuestSystem);*/
}

void QuestSystemTest::run()
{
	LOG("QuestSystemTest: run()");
}

bool QuestSystemTest::isComplete() const
{
	return true;
}
