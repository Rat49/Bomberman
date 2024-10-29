#pragma once
#include <string>
#include <map>
#include <vector>
#include "AssetTypes.hpp"

class AssetManager
{
public:
	AssetManager(const std::string& settingsPath);

	bool SetRootFolder(const std::string& rootFolderPath);

	void LoadAllAssets();

	bool LoadSound(const std::string& soundName, const std::string& soundPath);

	bool LoadSound(const std::string& soundPath);

	bool LoadTexture(const std::string& textureName, const std::string& texturePath);

	bool LoadTexture(const std::string& texturePath);

	bool LoadFont(const std::string& fontName, const std::string& fontPath);

	bool LoadFont(const std::string& fontPath);

	sf::SoundBuffer* GetSound(const AssetName& assetName);

	sf::Texture* GetTexture(const AssetName& assetName);

	sf::Font* GetFont(const AssetName& assetName);

private:
	std::string rootFolder;

	std::string settings;

	std::map<AssetName, sf::SoundBuffer> sounds;

	std::map<AssetName, sf::Texture> textures;

	std::map<AssetName, sf::Font> fonts;
};

