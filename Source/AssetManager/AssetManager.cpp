#include "AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/StringUtils.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSection.hpp"
#include <filesystem>

namespace {
	const std::string ABSOLUTE_ROOT_FOLDER = "RootFolder";
	const std::string ROOT                 = "root";
	const std::string RELATIVE_ROOT_FOLDER = "Game/";
}

AssetManager::AssetManager()
{
	rootFolder = "";
}

bool AssetManager::initialize(const std::string& settingsPath)
{
	Modules::Config->addFile(settingsPath);
	const ConfigFile& assetManagerSettings = Modules::Config->getFile(settingsPath);
	if (!assetManagerSettings.isSectionPresent(ABSOLUTE_ROOT_FOLDER))
	{
		return false;
	}
	rootFolder = assetManagerSettings.getSection(ABSOLUTE_ROOT_FOLDER).getValue(ROOT).getString();
	return true;
}

bool AssetManager::loadSound(const RelativeAssetPath& relativeSoundPath)
{
	auto it = sounds.find(relativeSoundPath);
	if (it != sounds.end())
	{
		LOG("Sound [$] already loaded", relativeSoundPath);
		return true;
	}

	auto soundBuffer = std::make_shared<sf::SoundBuffer>();
	std::string fullPath = getFullPath(relativeSoundPath);
	if (!soundBuffer->loadFromFile(fullPath))
	{
		return false;
	}

	sounds.emplace(relativeSoundPath, std::move(soundBuffer));
	return true;
}

bool AssetManager::loadTexture(const RelativeAssetPath& relativeTexturePath)
{
	auto it = textures.find(relativeTexturePath);
	if (it != textures.end())
	{
		LOG("Texture [$] already loaded", relativeTexturePath);
		return true;
	}

	auto texture = std::make_shared<sf::Texture>();
	std::string fullPath = getFullPath(relativeTexturePath);
	if (!texture->loadFromFile(fullPath))
	{
		return false;
	}

	textures.emplace(relativeTexturePath, std::move(texture));
	return true;
}

bool AssetManager::loadFont(const RelativeAssetPath& relativeFontPath)
{
	auto it = fonts.find(relativeFontPath);
	if (it != fonts.end())
	{
		LOG("Font [$] already loaded", relativeFontPath);
		return true;
	}

	auto font = std::make_shared<sf::Font>();
	std::string fullPath = getFullPath(relativeFontPath);
	if (!font->loadFromFile(fullPath))
	{
		return false;
	}

	fonts.emplace(relativeFontPath, std::move(font));
	return true;
}

std::shared_ptr <sf::SoundBuffer> AssetManager::getSound(const RelativeAssetPath& assetName)
{
	auto it = sounds.find(assetName);
	if (it == sounds.end())
	{
		LOG("Sound [$] not loaded", assetName);
		return nullptr;
	}
	return it->second;
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const RelativeAssetPath& assetName)
{
	auto it = textures.find(assetName);
	if (it == textures.end())
	{
		LOG("Texture [$] not loaded", assetName);
		return nullptr;
	}
	return it->second;
}

std::shared_ptr<sf::Font> AssetManager::getFont(const RelativeAssetPath& assetName)
{
	auto it = fonts.find(assetName);
	if (it == fonts.end())
	{
		LOG("Font [$] not loaded", assetName);
		return nullptr;
	}
	return it->second;
}

/**
 * @brief Returns absolute path.
 *
 * This function returns absolute path to the file.
 *
 * @param relativePath is the relative path to the file.
 *
 * @return The absolute path to the file, if the
 * relative path is incorrect returns empty string.
 **/
std::string AssetManager::getFullPath(const std::string& relativePath) const
{
	std::string path = relativePath;
	if (relativePath.find(RELATIVE_ROOT_FOLDER) != 0) {
		LOG("Relative path [$] is invalid", relativePath);
		return "";
	}
	path = relativePath.substr(RELATIVE_ROOT_FOLDER.length());
	return rootFolder + '/' + path;
}

