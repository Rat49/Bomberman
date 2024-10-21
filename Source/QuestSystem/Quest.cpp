#include "Quest.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "CreateObjective.hpp"
#include "EventSystem/EventSystem.hpp"

Quest::Quest(int32_t id, const std::string& questFile)
{
	questInfo.setId(id);
	questInfo.readQuestInfo(questFile);
	fileName = questFile;
}

Quest::~Quest()
{
	if (eventFinished != -1) {
		Modules::Events->unsubscribe(eventFinished, eventFinishedHandle);
	}
}

void Quest::startQuest()
{
	if (questProgress == QuestProgress::AVAILABLE)
	{
		currObjectiveCount = 0;
		questProgress = QuestProgress::IN_PROGRESS;
		instantiateCurrentObjective();
	}
}

void Quest::nextObjective()
{
	if (eventFinished != -1) {
		Modules::Events->unsubscribe(eventFinished, eventFinishedHandle);
	}
	if (currObjectiveCount+1 >= questInfo.getObjectivesCount()) {
		this->questProgress = QuestProgress::FINISHED;
	}
	else {
		currObjectiveCount++;
		instantiateCurrentObjective();
	}
}

void Quest::instantiateCurrentObjective()
{
	const std::string& questObjectivePrefix = "QuestObjective" + questInfo.getId() + std::to_string(currObjectiveCount);

	if (Modules::Config->isSectionPresent(fileName, questObjectivePrefix)) {
		int32_t description = Modules::Config->getValue(fileName, questObjectivePrefix, "description").getInt32();
		int32_t requiredCount = Modules::Config->getValue(fileName, questObjectivePrefix, "requiredCount").getInt32();

		this->eventFinished = Modules::Events->registerEvent();
		objectives.push_back(CreateObjective::getInstance().createObjective(description, requiredCount, eventFinished));
		this->eventFinishedHandle = Modules::Events->subscribe(eventFinished, std::bind(&Quest::nextObjective, this));
	}
}
