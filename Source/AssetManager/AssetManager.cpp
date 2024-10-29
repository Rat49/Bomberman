#include "AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/StringUtils.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSection.hpp"
#include <filesystem>

AssetManager::AssetManager()
{
	rootFolder = "";
}

bool AssetManager::initialize(const std::string& settingsPath)
{
	Modules::Config->addFile(settingsPath);
	const ConfigFile& assetManagerSettings = Modules::Config->getFile(settingsPath);
	if (!assetManagerSettings.isSectionPresent("RootFolder"))
	{
		return false;
	}
	rootFolder = assetManagerSettings.getSection("RootFolder").getValue("root").getString();
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

	sf::SoundBuffer soundBuffer;
	std::string fullPath = getFullPath(relativeSoundPath);

	if (!soundBuffer.loadFromFile(fullPath))
	{
		return false;
	}

	sounds.emplace(relativeSoundPath, soundBuffer);
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

	sf::Texture texture;
	std::string fullPath = getFullPath(relativeTexturePath);
	if (!texture.loadFromFile(fullPath))
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

	sf::Font font;
	std::string fullPath = getFullPath(relativeFontPath);
	if (!font.loadFromFile(fullPath))
	{
		return false;
	}

	fonts.emplace(relativeFontPath, std::move(font));
	return true;
}

sf::SoundBuffer* AssetManager::getSound(const RelativeAssetPath& assetName)
{
	auto it = sounds.find(assetName);
	if (it == sounds.end())
	{
		return nullptr;
	}
	return &it->second;
}

sf::Texture* AssetManager::getTexture(const RelativeAssetPath& assetName)
{
	auto it = textures.find(assetName);
	if (it == textures.end())
	{
		return nullptr;
	}
	return &it->second;
}

sf::Font* AssetManager::getFont(const RelativeAssetPath& assetName)
{
	auto it = fonts.find(assetName);
	if (it == fonts.end())
	{
		return nullptr;
	}
	return &it->second;
}

std::string AssetManager::getFullPath(const std::string& relativePath) const
{
	std::string path = relativePath;
	const std::string prefix = "Game/";
	if (relativePath.find(prefix) == 0) {
		path = relativePath.substr(prefix.length());
	}
	return rootFolder + '/' + path;
}

