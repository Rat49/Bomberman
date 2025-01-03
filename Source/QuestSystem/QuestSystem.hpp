#pragma once
#include "Quest.hpp"

class QuestSystem
{
public:
    void addQuest(const std::string& file, const std::string& questName);

private:
    std::vector<std::unique_ptr<Quest>> quests;
};