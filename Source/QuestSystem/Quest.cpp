#include "Quest.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "EventSystem/EventSystem.hpp"

namespace {
	const std::string REWARD = "reward";
}

Quest::Quest(const std::string& id, const std::string& fileName) : fileName(fileName), id(id)
{
	reward = Modules::Config->getValue(fileName, id, REWARD).getInt32();
}