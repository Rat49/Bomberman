#include "QuestSystem.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "QuestSystem/FailObjective.hpp"


void QuestSystem::addQuest(const std::string& file, const std::string& questName)
{
	//quests.push_back(std::make_unique<Quest>(questName, file));

	auto quest = std::make_unique<Quest>(questName, file);

    // Adding fail conditions
    quest->addFailCondition(std::make_unique<FailObjective>(Modules::Game->GAME_TIMER_FINISHED, Modules::Game->QUEST_FAILED));
    quest->addFailCondition(std::make_unique<FailObjective>(Modules::Game->PLAYER_DESTROYED, Modules::Game->QUEST_FAILED));

    quests.push_back(std::move(quest));
}
