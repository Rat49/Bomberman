#pragma once
#include <map>
#include <string>
#include <SFML/System/FileInputStream.hpp>
#include "PackageReaderTypes.hpp"
#include "AssetTypes.hpp"

class PackageReader
{
public:

	static bool loadFromPackage(RelativeAssetPath RelativeAssetPath, std::vector<char>& outputData);

	static bool loadMetadata();
	
private:
	static std::map<RelativeAssetPath, AssetMetadata> assetsMetadata;
};

