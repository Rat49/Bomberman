#include "Quest.hpp"

 const std::string& Quest::getQuestProgress() const
 {
	 static std::string fullStatus;
	 if (questProgress == QuestProgress::NOT_AVAILABLE) {
		 fullStatus = "This quest is not yet available";
	 }
	 else if (questProgress == QuestProgress::AVAILABLE) {
		 fullStatus = "This quest can be started";
	 }
	 else if (questProgress == QuestProgress::FINISHED)
	 {
		 fullStatus += "The quest has been completed!";
	 }
	 return fullStatus;
 }
