#pragma once
#include <map>
#include <string>
#include <SFML/System/FileInputStream.hpp>
#include "AssetTypes.hpp"

struct AssetMetadata
{
	std::string assetName;
	std::streamoff offset;
	std::streamoff size;
};

class PackageReader
{
public:
	PackageReader();

	//bool loadFromPackage(RelativeAssetPath RelativeAssetPath, std::vector<unsigned char>& outputData);

	std::shared_ptr<sf::Font> loadFontFromPackage(const RelativeAssetPath fontFile);
	
private:
	std::map<RelativeAssetPath, AssetMetadata> assetsMetadata;
	bool loadMetadata();
};

