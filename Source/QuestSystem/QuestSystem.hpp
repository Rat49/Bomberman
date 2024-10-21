#pragma once
#include "Quest.hpp"
#include "CreateObjective.hpp"
#include <memory>

class QuestSystem {
public:
	void addQuests(const std::string& file);

	void startQuest(int32_t id);

	void emitMyEvent(const EventType& name) const;
private:
	std::vector<std::unique_ptr<Quest>> quests;
};
