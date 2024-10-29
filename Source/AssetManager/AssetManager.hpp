#pragma once
#include <string>
#include <map>
#include <vector>
#include "AssetTypes.hpp"

class AssetManager
{
public:
	AssetManager();

	bool initialize(const std::string& rootFolderPath);

	bool loadSound(const RelativeAssetPath& soundPath);

	bool loadTexture(const RelativeAssetPath& texturePath);

	bool loadFont(const RelativeAssetPath& fontPath);

	sf::SoundBuffer* getSound(const RelativeAssetPath& assetName);

	sf::Texture* getTexture(const RelativeAssetPath& assetName);

	sf::Font* getFont(const RelativeAssetPath& assetName);

private:
	std::string rootFolder;

	std::map<RelativeAssetPath, sf::SoundBuffer> sounds;

	std::map<RelativeAssetPath, sf::Texture> textures;

	std::map<RelativeAssetPath, sf::Font> fonts;

	std::string AssetManager::getFullPath(const std::string& relativePath) const;
};

