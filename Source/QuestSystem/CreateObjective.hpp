#pragma once
#include <string>
#include <memory>
class BaseObjective;

class CreateObjective {
public:
	static CreateObjective& getInstance() {
		static CreateObjective instance;
		return instance;
	}

	std::unique_ptr<BaseObjective> createObjective(const std::string& description, int32_t requiredCnt);
};