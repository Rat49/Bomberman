#pragma once
#include "Quest.hpp"
#include <memory>

class QuestSystem {
private:
	std::vector<std::unique_ptr<Quest>> quests;
};