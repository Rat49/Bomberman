#pragma once

#include "BaseObjective.hpp"
#include "EventSystem/EventTypes.hpp"
#include <vector>
#include <memory>

class Quest 
{
public:
	Quest(const std::string& id, const std::string& fileName);

	const std::string& getId() const { return id; }

	const int32_t getReward() const { return reward; }

	const std::string& getFile() const { return fileName; }

	void addObjective(std::unique_ptr<BaseObjective> objective);
    void addFailCondition(std::unique_ptr<BaseObjective> failCondition);

    void checkCompletion();

private:
	std::string fileName;
	std::string id;
	int32_t reward;

	std::vector<std::unique_ptr<BaseObjective>> objectives;
    std::vector<std::unique_ptr<BaseObjective>> failConditions;
};