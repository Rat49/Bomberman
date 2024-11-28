#include "LevelData.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <Common/Modules.hpp>

namespace
{
	const std::string ATLAS_PATH = "atlasPath";
	const std::string LEVEL_PATH = "levelPath";
	const std::string TILESET_PATH = "tilesetPath";
	const std::string TILE_WIDTH = "tileWidth";
	const std::string TILE_HEIGHT = "tileHeight";
	const std::string ASSETS_CONFIG = "tilesetAssetsConfig";
	const std::string ID = "id";
}

bool LevelData::loadLevelConfigData(const std::string& configLevelPath)
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

		//load tileSet path
		m_tilesetPath = mySection.getValue(TILESET_PATH).getString();

		//load tileAssetsConfig
		m_tilesAssetsConfig = mySection.getValue(ASSETS_CONFIG).getString();

		//load tile width
		m_tileWidth = mySection.getValue(TILE_WIDTH).getInt32();

		//load tile height
		m_tileHeight = mySection.getValue(TILE_HEIGHT).getInt32();

		anyDataFound = true;
	}

	return anyDataFound;
}

bool LevelData::loadTilesetConfigData(const std::string& configTilesetPath)
{
	Modules::Config->addFile(configTilesetPath);
	const ConfigFile& tilestHandlingData = Modules::Config->getFile(configTilesetPath);

	bool anyDataFound = false;
	const auto& sections = tilestHandlingData.getAllSections();
	const std::vector<std::string> configValues = { ID };

	//read all sections
	for (const auto& section : sections)
	{
		//check if section exists
		if (!tilestHandlingData.isSectionPresent(section))
			break;

		//check if values exists
		if (!tilestHandlingData.getSection(section).areValuesPresent(configValues))
			break;

		const ConfigSection& mySection = tilestHandlingData.getSection(section);

		//set info using tile id as key 
		m_tilesetInfo[mySection.getValue(ID).getInt32()] = section;

		anyDataFound = true;
	}

	return anyDataFound;

}
