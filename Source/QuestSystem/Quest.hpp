#pragma once
#include "BaseObjective.hpp"
#include "EventSystem/EventTypes.hpp"

class Quest {
public:
	Quest(const std::string& id, const std::string& fileName);

	const std::string& getId() const { return id; }

	const int32_t getReward() const { return reward; }

	const std::string& getFile() const { return fileName; }

private:
	std::string fileName;
	std::string id;
	int32_t reward;
};