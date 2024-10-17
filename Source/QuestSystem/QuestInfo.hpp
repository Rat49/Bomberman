#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "BaseObjective.hpp"
#include "ConfigSystem/ConfigFile.hpp"

class QuestInfo {
public:
	void readQuestInfo(const std::string& file);

	const std::string& getDisplayName() const { return displayName; }
	void setDisplayName(const std::string& val) { displayName = val; }

	int32_t getReward() const { return reward; }
	void setReward(int32_t val) { reward = val; }

	int32_t getId() const { return id; }
	void setId(int32_t val) { id = val; }

private:
	int32_t id = 0;

	std::string displayName;
	int32_t reward = 0;
	int32_t objectivesCount = 0;

	std::vector<std::unique_ptr<BaseObjective>> objectives;
};