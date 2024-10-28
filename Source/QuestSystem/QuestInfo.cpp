#include "QuestInfo.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

namespace {
	const std::string DISPLAY_NAME = "displayName";
	const std::string REWARD = "reward";
	const std::string QUEST_INFO = "QuestInfo";
	const std::string OBJECTIVES_COUNT = "objectivesCount";
}

void QuestInfo::readQuestInfo(const std::string& file)
{
	const std::string questInfoPrefix = QUEST_INFO + std::to_string(id);

	displayName = Modules::Config->getValue(file, questInfoPrefix, DISPLAY_NAME).getString();
	reward = Modules::Config->getValue(file, questInfoPrefix, REWARD).getInt32();
	objectivesCount = Modules::Config->getValue(file, questInfoPrefix, OBJECTIVES_COUNT).getInt32();
}

const std::string& QuestInfo::getDisplayName() const
{
	return displayName;
}

void QuestInfo::setDisplayName(const std::string& val)
{
	displayName = val;
}

int32_t QuestInfo::getReward() const
{
	return reward;
}

void QuestInfo::setReward(int32_t val)
{
	reward = val;
}

int32_t QuestInfo::getObjectivesCount() const
{
	return objectivesCount;
}

void QuestInfo::setObjectivesCount(int32_t val)
{
	objectivesCount = val;
}

std::string QuestInfo::getId() const
{
	return std::to_string(id);
}

void QuestInfo::setId(int32_t val)
{
	id = val;
}