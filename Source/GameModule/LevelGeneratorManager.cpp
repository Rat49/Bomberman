#include "LevelGeneratorManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"

namespace
{
	const std::string ID				= "id";
	const std::string LEVEL_TYPE		= "levelType";
	const std::string ENEMY_COUNT		= "enemyCount";
	const std::string BREAKABLE_COUNT	= "breakableCount";
	const std::string BOOSTERS_COUNT	= "boostersCount";
}

bool LevelGeneratorManager::initialize(const std::string& configPath)
{
	//init config file
	Modules::Config->addFile(configPath);
	const ConfigFile& LevelManagerFile = Modules::Config->getFile(configPath);

	bool valuesFound = false;
	std::vector<std::string> configNames = { ID, LEVEL_TYPE, ENEMY_COUNT, BREAKABLE_COUNT, BOOSTERS_COUNT };

	//check all sections
	const auto& sections = LevelManagerFile.getAllSections();
	for (const auto& sectionName : sections)
	{

		if (!LevelManagerFile.isSectionPresent(sectionName))
			break;

		if (LevelManagerFile.getSection(sectionName).areValuesPresent(configNames))
		{
			const ConfigSection& mySection = LevelManagerFile.getSection(sectionName);

			//store values in map
			m_levelConfig.levelType = static_cast<GameLevelType>(mySection.getValue(LEVEL_TYPE).getInt32());
			m_levelConfig.enemyCount		= mySection.getValue(ENEMY_COUNT).getInt32();
			m_levelConfig.breakableCount	= mySection.getValue(BREAKABLE_COUNT).getInt32();
			m_levelConfig.boostersCount		= mySection.getValue(BOOSTERS_COUNT).getInt32();

			m_levelConfigData[mySection.getValue(ID).getInt32()] = m_levelConfig;

			valuesFound = true;
		}
	}
	return valuesFound;
}

bool LevelGeneratorManager::createLevel(uint32_t levelId)
{
	auto it = m_levelConfigData.find(levelId);
	if (it == m_levelConfigData.end())
	{
		LOG("Level with id [$] not found (not initialized from file).", levelId);
		return false;
	}

	const LevelConfig& config = it->second;
	m_levelGenerator = std::make_unique<LevelGenerator>();

	if (!m_levelGenerator->Initialize(config))
	{
		LOG("Failed to create level with id : [$]", levelId);
		return false;
	}

	return true;
}

void LevelGeneratorManager::drawLevel(sf::RenderTarget& target) const
{
	if (!m_levelGenerator)
	{
		LOG("Failed to draw level. Level generator is not initialized.");
		return;
	}

	m_levelGenerator->draw(target);
}