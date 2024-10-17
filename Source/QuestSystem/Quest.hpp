#pragma once
#include "QuestInfo.hpp"

class Quest {
public:
	Quest(int32_t id) { questInfo.setId(id); }

	enum QuestProgress {
		NOT_AVAILABLE, AVAILABLE, IN_PROGRESS, FINISHED
	};
	const std::string& getQuestProgress() const;

private:
	QuestInfo questInfo;
	QuestProgress questProgress = QuestProgress::NOT_AVAILABLE;
	int32_t currObjectiveCount = 0;
};