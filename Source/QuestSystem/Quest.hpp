#pragma once
#include "QuestInfo.hpp"
#include "BaseObjective.hpp"
#include "EventSystem/EventTypes.hpp"

class Quest {
public:
	Quest(int32_t id, const std::string& questFile);

	~Quest();

	enum class QuestProgress {
		NOT_AVAILABLE, AVAILABLE, IN_PROGRESS, FINISHED
	};

	void startQuest();

	void instantiateCurrentObjective();

	void nextObjective();

private:
	QuestInfo questInfo;
	QuestProgress questProgress = QuestProgress::AVAILABLE;
	int32_t currObjectiveCount = -1;
	std::string fileName;

	int32_t eventFinished = -1;
	FunctionHandle eventFinishedHandle = -1;

	std::vector<std::unique_ptr<BaseObjective>> objectives;
};