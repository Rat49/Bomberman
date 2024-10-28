#include "QuestSystem.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

void QuestSystem::addQuest(const std::string& file, const std::string& questName)
{
	quests.push_back(std::make_unique<Quest>(questName, file));
}
