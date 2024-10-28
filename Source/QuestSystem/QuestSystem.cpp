#include "QuestSystem.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

void QuestSystem::addQuests(const std::string& file)
{
	int32_t i = 0;
	const std::string& questInfoPrefix = "QuestInfo";
	while (Modules::Config->isSectionPresent(file, questInfoPrefix + std::to_string(i))) {
		quests.push_back(std::make_unique<Quest>(i++, file));
	}
}

void QuestSystem::startQuest(int32_t id)
{
	if (quests.size() > id) {
		quests[id]->startQuest();
	}
}
