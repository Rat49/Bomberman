#include "Common/Modules.hpp"
#include "QuestSystem/QuestSystem.hpp"
#include "QuestManager.hpp"

QuestManager::QuestManager(const std::string& file)
{
	Modules::Quests->addQuests(file);
	CreateObjective::getInstance().registerAllEvents();
}

void QuestManager::startQuest(int32_t id)
{
	Modules::Quests->startQuest(id);
}

void QuestManager::emitMyEvent(const EventType& name) const
{
	CreateObjective::getInstance().emitEvent(name);
}