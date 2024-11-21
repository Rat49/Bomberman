#include "TileManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "AssetManager/AssetManager.hpp"

namespace
{
	const std::string ID = "id";
	const std::string X = "x";
	const std::string Y = "y";;
	const std::string TILE_STATE = "state";
	const std::string ATLAS_PATH = "Game/Textures/levelAtlas.png";
	const std::string PATH = "../../Data/Config/TileAssetsConfig.ini";
	const int8_t ATLAS_SPRITE_SIZE = 64;
	const int8_t GAME_SPRITE_SIZE = 32;
}

TileManager::TileManager()
{
	m_atlasTexture = nullptr;
}

void TileManager::initialize()
{
	m_atlasTexture = Modules::Assets->getTexture(ATLAS_PATH);

	Modules::Config->addFile(PATH);
	const ConfigFile& tileTexturesSettings = Modules::Config->getFile(PATH);
	const auto& sections = tileTexturesSettings.getAllSections();

	for (const auto& section : sections)
	{
		TileID id     = tileTexturesSettings.getSection(section).getValue(ID).getInt32();
		int32_t x     = tileTexturesSettings.getSection(section).getValue(X).getInt32();
		int32_t y     = tileTexturesSettings.getSection(section).getValue(Y).getInt32();
		float scale   = (float)(GAME_SPRITE_SIZE / (float)ATLAS_SPRITE_SIZE);

		Tile newTile;
		sf::IntRect newRect(x, y, ATLAS_SPRITE_SIZE, ATLAS_SPRITE_SIZE);
		newTile.initialize(id, newRect, m_atlasTexture);
		newTile.setScale(scale, scale);
		m_availableTiles.emplace(id, std::make_shared<Tile>(std::move(newTile)));
	}
}

std::shared_ptr<Tile> TileManager::getTile(TileID tileID)
{
	auto it = m_availableTiles.find(tileID);
	if (it == m_availableTiles.end())
	{
		LOG("Tile with id:[$] not found", tileID);
		return nullptr;
	}
	return it->second;
}