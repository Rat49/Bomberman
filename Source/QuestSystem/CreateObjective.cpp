#include "CreateObjective.hpp"
#include "ObjectivePlaceBombs.hpp"

std::unique_ptr<BaseObjective> CreateObjective::createObjective(const std::string& description, int32_t requiredCnt)
{
	if (description == "Place bombs") {
		return std::make_unique<ObjectivePlaceBombs>(requiredCnt);
	}
	else {
		return nullptr;
	}
}
