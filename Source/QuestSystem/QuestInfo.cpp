#include "QuestInfo.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "CreateObjective.hpp"

void QuestInfo::readQuestInfo(const std::string& file)
{
	const std::string questInfoPrefix = "QuestInfo" + id;
	const std::string questObjectivePrefix = "QuestObjective" + id;

	displayName = Modules::Config->getValue(file, questInfoPrefix, "displayName").getString();
	reward = Modules::Config->getValue(file, questInfoPrefix, "reward").getInt32();
	objectivesCount = Modules::Config->getValue(file, questInfoPrefix, "objectivesCnt").getInt32();

	std::string description;
	int requiredCount;

	for (int i = 0; i < objectivesCount; i++) {
		description = Modules::Config->getValue(file, questObjectivePrefix + std::to_string(i), "description").getString();
		requiredCount = Modules::Config->getValue(file, questObjectivePrefix + std::to_string(i), "requiredCount").getInt32();
		objectives.push_back(CreateObjective::getInstance().createObjective(description, requiredCount));
	}
}
