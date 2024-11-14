#include "PackageReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Common/Logs.hpp"
#include "Common/StringUtils.hpp"
#include <filesystem>

std::map<std::string, AssetMetadata> PackageReader::assetsMetadata;

namespace
{
	const std::string METADATA_FILE = "Package/bomberman.mtd";
	const std::string PACKAGE_FILE = "Package/bomberman.pkg";
	const std::string CIPHER_KEY    = "VERYSECUREKEY";
}

bool PackageReader::loadMetadata()
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

bool PackageReader::loadFromPackage(RelativeAssetPath relativeAssetPath, std::vector<char>& outputData) 
{
	std::ifstream packageFile(PACKAGE_FILE, std::ios::binary);
	if (!packageFile) {
		LOG("Could not read file [$]", PACKAGE_FILE);
		return false;
	}
	
	packageFile.seekg(assetsMetadata[relativeAssetPath].offset);
	outputData.resize(assetsMetadata[relativeAssetPath].size);
	
	if (!packageFile.read(outputData.data(), outputData.size())) {
		std::cerr << "Failed to read font data from package!" << std::endl;
		return false;
	}

	return true;
}