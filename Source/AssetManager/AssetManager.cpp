#include "AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/StringUtils.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include <fstream>

namespace 
{
	const std::string ABSOLUTE_ROOT_FOLDER = "RootFolder";
	const std::string ROOT                 = "root";
	const std::string USE_PACKAGE          = "UsePackage";
	const std::string VALUE                = "value";
	const std::string RELATIVE_ROOT_FOLDER = "Game/";
	const std::string METADATA_FILE        = "Package/bomberman.mtd";
	const std::string PACKAGE_FILE         = "Package/bomberman.pkg";
	const std::string CIPHER_KEY           = "VERYSECUREKEY";
	const std::string SETTINGS_PATH =      "../../Data/Config/assetmngr_config.ini";
}

AssetManager::AssetManager()
{
	rootFolder = "";
	usePackage = false;
}

bool AssetManager::initialize()
{
	Modules::Config->addFile(SETTINGS_PATH);
	const ConfigFile& assetManagerSettings = Modules::Config->getFile(SETTINGS_PATH);
	if (!assetManagerSettings.isSectionPresent(ABSOLUTE_ROOT_FOLDER))
	{
		return false;
	}
	rootFolder = assetManagerSettings.getSection(ABSOLUTE_ROOT_FOLDER).getValue(ROOT).getString();

	#ifdef FINAL
		usePackage = true;
	#else
		usePackage = assetManagerSettings.getSection(USE_PACKAGE).getValue(VALUE).getBool();
	#endif

	if (usePackage && !loadMetadata())
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
		if (!loadData(assetName, fullPath, soundData))
		{
			LOG("Could not load sound data from file: [$]", assetName);
			return nullptr;
		}
	}
	else
	{
		if (!loadData(assetName, PACKAGE_FILE, soundData))
		{
			LOG("Could not load sound data from pacakge");
			return nullptr;
		}
	}

	if (!soundBuffer->loadFromMemory(soundData.data(), soundData.size())) {
		LOG("Could not load sound from memory");
		return nullptr;
	}

	sounds.emplace(assetName, std::move(soundBuffer));

	return sounds[assetName];
}

std::shared_ptr <sf::Music> AssetManager::getMusic(const RelativeAssetPath assetName)
{
	auto it = musics.find(assetName);
	if (it != musics.end())
	{
		return it->second.first;
	}

	auto music = std::make_shared<sf::Music>();
	std::vector<char> musicData;
	if (!usePackage)
	{
		std::string fullPath = getFullPath(assetName);
		if (!loadData(assetName, fullPath, musicData))
		{
			LOG("Failed to load musci data from file : [$]", fullPath);
			return nullptr;
		}
	}
	else
	{
		if (!loadData(assetName, PACKAGE_FILE, musicData))
		{
			LOG("Could not load music data from package");
			return nullptr;
		}
	}

	if (!music->openFromMemory(musicData.data(), musicData.size()))
	{
		LOG("Could not open music from memory: [$]", assetName);
		return nullptr;
	}

	musics.emplace(assetName, std::make_pair(std::move(music), std::move(musicData)));

	return musics[assetName].first;
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
		if (!loadData(assetName, fullPath, textureData))
		{
			LOG("Could not load texture data from file: [$]", assetName);
			return nullptr;
		}
	}
	else
	{
		if (!loadData(assetName, PACKAGE_FILE, textureData))
		{
			LOG("Could not load texture data from pacakge");
			return nullptr;
		}
	}

	if (!texture->loadFromMemory(textureData.data(), textureData.size())) {
		LOG("Could not load texture from memory: [$]", assetName);
		return nullptr;
	}

	textures.emplace(assetName, std::move(texture));

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
		if (!loadData(assetName, fullPath, fontData))
		{
			LOG("Could not load font data from file: [$]", assetName);
			return nullptr;
		};
	}
	else
	{
		if (!loadData(assetName, PACKAGE_FILE, fontData))
		{
			LOG("Could not load font data from pacakge");
			return nullptr;
		}
	}

	if (!font->loadFromMemory(fontData.data(), fontData.size())) {
		LOG("Could not load font from memory: [$]", assetName);
		return nullptr;
	}

	fonts.emplace(assetName, std::make_pair(std::move(font), std::move(fontData)));

	return fonts[assetName].first;
}

std::vector<char> AssetManager::getLevel(const RelativeAssetPath& assetName)
{
	auto it = levels.find(assetName);
	if (it != levels.end())
	{
		return it->second;
	}

	std::vector<char> levelData;

	if (!usePackage)
	{
		std::string fullPath = getFullPath(assetName);
		if (!loadData(assetName, fullPath, levelData))
		{
			LOG("Could not load level data from file: [$]", assetName);
			return {};
		}
	}
	else
	{
		if (!loadData(assetName, PACKAGE_FILE, levelData))
		{
			LOG("Could not load level data from memory : [$]", assetName);
			return {};
		}
	}

	levels.emplace(assetName, std::move(levelData));

	return levels[assetName];


}

bool AssetManager::loadMetadata()
{
	std::ifstream metadataFile(METADATA_FILE, std::ios::beg);
	if (!metadataFile)
	{
		LOG("Unable to open file [$]", METADATA_FILE);
		return false;
	}

	std::string metadata((std::istreambuf_iterator<char>(metadataFile)), std::istreambuf_iterator<char>());
	StringUtils::cipherText(metadata, CIPHER_KEY);

	std::istringstream ss(metadata);
	std::string line;
	AssetMetadata newAssetMetadata = {};
	while (std::getline(ss, line))
	{
		std::vector<std::string> tokens;
		StringUtils::tokenize(line, ';', tokens);
		newAssetMetadata.assetName = tokens[0];
		newAssetMetadata.size      = static_cast<std::streamoff>(stoll(tokens[1]));
		newAssetMetadata.offset    = static_cast<std::streamoff>(stoll(tokens[2]));
		assetsMetadata.emplace(std::move(tokens[0]), std::move(newAssetMetadata));
	}

	for (const auto& el : assetsMetadata)
	{
		LOG("$:$:$", el.first, el.second.size, el.second.offset);
	}

	return true;
}

bool AssetManager::loadData(const RelativeAssetPath& assetName, const std::string& fileToOpen, std::vector<char>& outputData)
{
	std::ifstream file(fileToOpen, std::ios::binary | std::ios::beg);
	if (!file) {
		LOG("Could not read file [$]", fileToOpen);
		return false;
	}

 	if(usePackage)
	{
		file.seekg(assetsMetadata[assetName].offset);
		outputData.resize(assetsMetadata[assetName].size);
	}
	else
	{
		file.seekg(0, std::ios::end);
		outputData.resize(file.tellg());
		file.seekg(0, std::ios::beg);
	}

	if (!file.read(outputData.data(), outputData.size())) {
		LOG("Failed to read data from file: [$]", fileToOpen);
		return false;
	}

	return true;
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
