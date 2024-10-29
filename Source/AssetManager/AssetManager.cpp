#include "AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/StringUtils.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSection.hpp"
#include <filesystem>

AssetManager::AssetManager(const std::string& settingsPath)
{
	Modules::Config->addFile(settingsPath);
	const ConfigFile& assetManagerSettings = Modules::Config->getFile(settingsPath);
	if (assetManagerSettings.isSectionPresent("RootFolder"))
	{
		rootFolder = assetManagerSettings.getSection("RootFolder").getValue("root").getString();
	}
	else {
		rootFolder = "";
	}
	settings = std::string(settingsPath);
}

bool AssetManager::SetRootFolder(const std::string& rootFolderPath)
{
	if (rootFolder != "")
	{
		return false;
	}
	rootFolder = rootFolderPath;
	return true;
}

bool AssetManager::LoadSound(const std::string& soundName, const std::string& soundPath)
{
	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile(rootFolder + soundPath))
	{
		return false;
	}
	sounds.emplace(soundName, std::move(soundBuffer));
	return true;
}

bool AssetManager::LoadSound(const std::string& soundPath)
{
	sf::SoundBuffer soundBuffer;
	std::vector<std::string> tmp = StringUtils::explode(rootFolder + soundPath, '/');
	std::string soundName        = StringUtils::explode(tmp[tmp.size() - 1], '.')[0];
	if (soundBuffer.loadFromFile(rootFolder + soundPath))
	{
		sounds.emplace(soundName, soundBuffer);
		return true;
	}
	return false;
}

bool AssetManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
	sf::Texture texture;
	if (!texture.loadFromFile(rootFolder + texturePath))
	{
		return false;
	}
	textures.emplace(textureName, std::move(texture));
	return true;
}

bool AssetManager::LoadTexture(const std::string& texturePath)
{
	sf::Texture texture;
	std::vector<std::string> tmp = StringUtils::explode(rootFolder + texturePath, '/');
	std::string textureName      = StringUtils::explode(tmp[tmp.size() - 1], '.')[0];
	if (!texture.loadFromFile(rootFolder + texturePath))
	{
		return false;
	}
	textures.emplace(textureName, std::move(texture));
	return true;
}

bool AssetManager::LoadFont(const std::string & fontName, const std::string & fontPath)
{
	sf::Font font;
	if (!font.loadFromFile(rootFolder + fontPath))
	{
		return false;
	}
	fonts.emplace(fontName, std::move(font));
	return true;
}

bool AssetManager::LoadFont(const std::string& fontPath)
{
	sf::Font font;
	std::vector<std::string> tmp = StringUtils::explode(rootFolder + fontPath, '/');
	std::string fontName         = StringUtils::explode(tmp[tmp.size() - 1], '.')[0];
	if (!font.loadFromFile(rootFolder + fontPath))
	{
		return false;
	}
	fonts.emplace(fontName, std::move(font));
	return true;
}

void AssetManager::LoadAllAssets()
{
	Modules::Config->addFile(rootFolder);
	const ConfigFile& managerSettings = Modules::Config->getFile(settings);
	const auto& sections = managerSettings.getAllSections();

	for (const auto& section : sections)
	{
		if (!managerSettings.isSectionPresent(section)) break;
		if (managerSettings.getSection(section).areValuesPresent({ "name", "type" }))
		{
			ConfigSection folderSection = managerSettings.getSection(section);
			std::string folderName = folderSection.getValue("name").getString();
			std::string folderAssetsType = folderSection.getValue("type").getString();
			std::string folderPath = rootFolder + "/" + folderName;

			if (folderAssetsType == "sound")
			{
				for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
					if (entry.is_regular_file()) {
						std::string soundPath = entry.path().string();
						std::string soundName = entry.path().stem().string();
						Modules::Assets->LoadSound(soundName, soundPath);
					}
				}
			}
			else if (folderAssetsType == "texture")
			{
				for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
					if (entry.is_regular_file()) {
						std::string texturePath = entry.path().string();
						std::string textureName = entry.path().stem().string();
						Modules::Assets->LoadTexture(textureName, texturePath);
					}
				}
			}
			else if (folderAssetsType == "font")
			{
				for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
					if (entry.is_regular_file()) {
						std::string fontPath = entry.path().string();
						std::string fontName = entry.path().stem().string();
						Modules::Assets->LoadFont(fontName, fontPath);
					}
				}
			}
			else {
				LOG("Section [$] invalid type", section);
			}
		}
		else
		{
			LOG("Section [$] is not proper folder", section);
		}
	}
}

sf::SoundBuffer* AssetManager::GetSound(const AssetName& assetName)
{
	auto it = sounds.find(assetName);
	if (it == sounds.end())
	{
		return nullptr;
	}
	return &it->second;
}


sf::Texture* AssetManager::GetTexture(const AssetName& assetName)
{
	auto it = textures.find(assetName);
	if (it == textures.end())
	{
		return nullptr;
	}
	return &it->second;
}

sf::Font* AssetManager::GetFont(const AssetName& assetName)
{
	auto it = fonts.find(assetName);
	if (it == fonts.end())
	{
		return nullptr;
	}
	return &it->second;
}

