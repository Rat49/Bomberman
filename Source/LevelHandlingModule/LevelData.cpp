#include "LevelData.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <Common/Modules.hpp>

namespace
{
	const std::string ATLAS_PATH = "atlasPath";
	const std::string LEVEL_PATH = "levelPath";
	const std::string TILE_WIDTH = "tileWidth";
	const std::string TILE_HEIGHT = "tileHeight";
}

bool LevelData::loadLevelData(const std::string& configLevelPath)
{
	Modules::Config->addFile(configLevelPath);
	const ConfigFile& levelHandlingData = Modules::Config->getFile(configLevelPath);

	bool anyDataFound = false;
	const auto& sections = levelHandlingData.getAllSections();
	const std::vector<std::string> configValues = { ATLAS_PATH, LEVEL_PATH, TILE_WIDTH, TILE_HEIGHT };

	//read all sections
	for (const auto& section : sections)
	{
		//check if section exists
		if (!levelHandlingData.isSectionPresent(section))
			break;

		//check if values exists
		if (!levelHandlingData.getSection(section).areValuesPresent(configValues))
			break;

		const ConfigSection& mySection = levelHandlingData.getSection(section);

		//load atlas path
		m_atlasPath = mySection.getValue(ATLAS_PATH).getString();

		//load level path
		m_levelPath = mySection.getValue(LEVEL_PATH).getString();

		//load tile width
		m_tileWidth = mySection.getValue(TILE_WIDTH).getInt32();

		//load tile height
		m_tileHeight = mySection.getValue(TILE_HEIGHT).getInt32();

		anyDataFound = true;
	}

	return anyDataFound;
}
