#include "AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/StringUtils.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSection.hpp"
#include "PackageReader.hpp"
#include <filesystem>

namespace 
{
	const std::string ABSOLUTE_ROOT_FOLDER = "RootFolder";
	const std::string ROOT                 = "root";
	const std::string USE_PACKAGE          = "UsePackage";
	const std::string VALUE                = "value";
	const std::string RELATIVE_ROOT_FOLDER = "Game/";
}

AssetManager::AssetManager()
{
	rootFolder = "";
	usePackage = false;
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
	usePackage = assetManagerSettings.getSection(USE_PACKAGE).getValue(VALUE).getBool();

	if (usePackage && !PackageReader::loadMetadata())
	{
		LOG("Could not load .package metadata");
		return false;
	}

	return true;
}

std::shared_ptr <sf::SoundBuffer> AssetManager::getSound(const RelativeAssetPath& assetName)
{
	auto it = sounds.find(assetName);
	if (it != sounds.end())
	{
		return it->second;
	}

	auto soundBuffer = std::make_shared<sf::SoundBuffer>();
	std::vector<char> soundData;
	if (!usePackage)
	{
		std::string fullPath = getFullPath(assetName);
		if (!soundBuffer->loadFromFile(fullPath))
		{
			LOG("Could not load sound from file");
			return false;
		}
		sounds.emplace(assetName, std::move(soundBuffer));
	}
	else
	{
		if (!PackageReader::loadFromPackage(assetName, soundData))
		{
			LOG("Could not load sound data from pacakge");
			return nullptr;
		}

		if (!soundBuffer->loadFromMemory(soundData.data(), soundData.size())) {
			LOG("Could not load sound from memory");
			return nullptr;
		}
		sounds.emplace(assetName, std::move(soundBuffer));
	}

	return sounds[assetName];
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const RelativeAssetPath& assetName)
{
	auto it = textures.find(assetName);
	if (it != textures.end())
	{
		return it->second;
	}
	
	auto texture = std::make_shared<sf::Texture>();
	std::vector<char> textureData;
	if (!usePackage)
	{
		std::string fullPath = getFullPath(assetName);
		if (!texture->loadFromFile(fullPath))
		{
			LOG("Could not load texture from file: [$]", assetName);
			return nullptr;
		}
		textures.emplace(assetName, std::move(texture));
	}
	else
	{
		if (!PackageReader::loadFromPackage(assetName, textureData))
		{
			LOG("Could not load texture data from pacakge");
			return nullptr;
		}

		if (!texture->loadFromMemory(textureData.data(), textureData.size())) {
			LOG("Could not load texture from memory: [$]", assetName);
			return nullptr;
		}
		textures.emplace(assetName, std::move(texture));
	}

	return textures[assetName];
}

std::shared_ptr<sf::Font> AssetManager::getFont(const RelativeAssetPath& assetName)
{
	auto it = fonts.find(assetName);
	if (it != fonts.end())
	{
		return it->second.first;
	} 

	auto font = std::make_shared<sf::Font>();
	std::vector<char> fontData;
	if(!usePackage)
	{
		std::string fullPath = getFullPath(assetName);
		if (!font->loadFromFile(fullPath))
		{
			LOG("Could not load font from file: [$]", assetName);
			return nullptr;
		}
		fonts.emplace(assetName, std::make_pair(std::move(font), std::move(fontData)));
	}
	else
	{
		if (!PackageReader::loadFromPackage(assetName, fontData))
		{
			LOG("Could not load  font data from pacakge");
			return nullptr;
		}

		if (!font->loadFromMemory(fontData.data(), fontData.size())) {
			LOG("Could not load font from memory: [$]", assetName);
			return nullptr;
		}
		fonts.emplace(assetName, std::make_pair(std::move(font), std::move(fontData)));
	}

	return fonts[assetName].first;
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

void AssetManager::terminate()
{
}