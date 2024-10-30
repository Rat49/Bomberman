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

	std::shared_ptr <sf::SoundBuffer> getSound(const RelativeAssetPath& assetName);

	std::shared_ptr<sf::Texture> getTexture(const RelativeAssetPath& assetName);

	std::shared_ptr<sf::Font> getFont(const RelativeAssetPath& assetName);

private:
	std::string rootFolder;

	std::map<RelativeAssetPath, std::shared_ptr<sf::SoundBuffer>> sounds;

	std::map<RelativeAssetPath, std::shared_ptr<sf::Texture>> textures;

	std::map<RelativeAssetPath, std::shared_ptr<sf::Font>> fonts;

	std::string AssetManager::getFullPath(const std::string& relativePath) const;
};

