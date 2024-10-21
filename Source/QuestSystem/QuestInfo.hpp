#pragma once
#include <string>
#include <iostream>
#include "ConfigSystem/ConfigFile.hpp"

class QuestInfo {
public:
	void readQuestInfo(const std::string& file);

	const std::string& getDisplayName() const;
	void setDisplayName(const std::string& val);

	int32_t getReward() const;
	void setReward(int32_t val);

	int32_t getObjectivesCount() const;
	void setObjectivesCount(int32_t val);

	std::string getId() const;
	void setId(int32_t val);

private:
	int32_t id = 0;

	std::string displayName;
	int32_t reward = 0;
	int32_t objectivesCount = 0;
};