#include "SaveSystemTest.hpp"
#include "Common/Modules.hpp"
#include "SaveSystem/SaveSystem.hpp"
#include "Common/Logs.hpp"

namespace 
{
	const std::string TEST_SAVE = "Test_Save";
}

const std::string& SaveSystemTest::getName() const
{
	return m_name;
}

void SaveSystemTest::setup()
{
	m_isComplete = false;

	std::unordered_map<std::string, std::string> gameData;
	gameData["PlayerName"] = "Lazar";
	gameData["PlayerLevel"] = "10";
	gameData["PlayerScore"] = "400";
	gameData["TimeLeft"] = "20.12";

	Modules::Save->saveGameData(TEST_SAVE, gameData);
}

void SaveSystemTest::run()
{
	std::unordered_map<std::string, std::string> mapToStoreData;
	
	if (Modules::Save->loadGameData(TEST_SAVE, mapToStoreData))
	{
		for (auto datas : mapToStoreData)
		{
			LOG("[$] = [$]" , datas.first, datas.second);
		}
	}

	m_isComplete = true;
}

void SaveSystemTest::update(float, sf::RenderWindow*)
{}

bool SaveSystemTest::isComplete() const
{
	return m_isComplete;
}
