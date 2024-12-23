#include "QuestSystem.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "QuestSystem/FailObjective.hpp"
#include "EventSystem/EventTypes.hpp"


void QuestSystem::addQuest(const std::string& file, const std::string& questName)
{
	//quests.push_back(std::make_unique<Quest>(questName, file));

	auto quest = std::make_unique<Quest>(questName, file);

    // Adding fail conditions
    quest->addFailCondition(std::make_unique<FailObjective>(EventTypes::GAME_TIMER_FINISHED, EventTypes::QUEST_FAILED));
    quest->addFailCondition(std::make_unique<FailObjective>(EventTypes::PLAYER_DESTROYED, EventTypes::QUEST_FAILED));

    quests.push_back(std::move(quest));
}
