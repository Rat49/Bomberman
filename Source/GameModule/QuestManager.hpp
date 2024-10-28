#pragma once
#include "CreateObjective.hpp"
#include <memory>

class QuestManager {
public:
	QuestManager(const std::string& file);

	void startQuest(int32_t id);

	void emitMyEvent(const EventType& name) const;	
};
