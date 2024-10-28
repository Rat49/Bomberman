#pragma once
#include "Quest.hpp"

class QuestSystem {
public:
	void addQuests(const std::string& file);

	void startQuest(int32_t id);
private:
	std::vector<std::unique_ptr<Quest>> quests;
};