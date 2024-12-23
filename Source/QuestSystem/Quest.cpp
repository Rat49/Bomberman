#include "Quest.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "EventSystem/EventSystem.hpp"

namespace
{
	const std::string REWARD = "reward";
}

Quest::Quest(const std::string& id, const std::string& fileName) : fileName(fileName), id(id)
{
	reward = Modules::Config->getValue(fileName, id, REWARD).getInt32();
}

void Quest::addObjective(std::unique_ptr<BaseObjective> objective)
{
    objectives.push_back(std::move(objective));
}

void Quest::addFailCondition(std::unique_ptr<BaseObjective> failCondition)
{
    failConditions.push_back(std::move(failCondition));
}

void Quest::checkCompletion()
{
    // Checking all goals
    /*for (const auto& objective : objectives)
    {
        objective->checkCompletion();
    }*/

    // Checking all fail conditions
    for (const auto& failCondition : failConditions)
    {
        failCondition->checkCompletion();
    }
}
