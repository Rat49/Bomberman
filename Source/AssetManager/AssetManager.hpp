#pragma once
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetTypes.hpp"
#include "BaseModule/BaseModule.hpp"

class AssetManager : public BaseModule
{
public:
	AssetManager();

	bool initialize(const std::string& rootFolderPath);

	std::shared_ptr <sf::SoundBuffer> getSound(const RelativeAssetPath& assetName);

	std::shared_ptr<sf::Texture> getTexture(const RelativeAssetPath& assetName);

	std::shared_ptr<sf::Font> getFont(const RelativeAssetPath& assetName);

	void terminate() override;

private:
	std::string rootFolder;

	bool usePackage;

	std::map<RelativeAssetPath, std::shared_ptr<sf::SoundBuffer>> sounds;

	std::map<RelativeAssetPath, std::shared_ptr<sf::Texture>> textures;

	std::map<RelativeAssetPath, std::pair<std::shared_ptr<sf::Font>, std::vector<char>>> fonts;

	std::map<RelativeAssetPath, AssetMetadata> assetsMetadata;

	std::string AssetManager::getFullPath(const std::string& relativePath) const;

	bool loadData(const RelativeAssetPath& assetName, const std::string& fileToOpen, std::vector<char>& outputData);

	bool loadMetadata();
};

