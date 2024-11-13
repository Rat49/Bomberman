#include "PackageReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Common/Logs.hpp"
#include "Common/StringUtils.hpp"
#include <filesystem>

namespace
{
	const std::string METADATA_FILE = "Package/bomberman.mtd";
	const std::string PACKAGE_FILE = "Package/bomberman.pkg";
	const std::string CIPHER_KEY    = "VERYSECUREKEY";
}

PackageReader::PackageReader()
{
	loadMetadata();
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

//bool PackageReader::loadFromPackage(RelativeAssetPath relativeAssetPath, std::vector<unsigned char>& outputData) 
//{
//	std::ifstream packageFile( PACKAGE_FILE, std::ifstream::binary | std::ios::beg);
//	if (!packageFile)
//	{
//		LOG("Could not read file [$]", PACKAGE_FILE);
//		return false;
//	}
//
//	//packageFile.seekg(assetsMetadata[relativeAssetPath].offset);
//	LOG("TELLG $", packageFile.tellg());
//	//outputData.resize(assetsMetadata[relativeAssetPath].size );
//	//auto start = &*outputData.begin();
//	//packageFile.read(outputData.data(), assetsMetadata[relativeAssetPath].size);
//	outputData.assign(std::istreambuf_iterator<char>(packageFile), std::istreambuf_iterator<char>());
//	LOG("OUTPUT SIZEEE $", outputData.size());
//	packageFile.close();
//	return true;
//}

std::shared_ptr<sf::Font> PackageReader::loadFontFromPackage(const RelativeAssetPath fontFile) {
	sf::Font font;
	std::ifstream packageFile(PACKAGE_FILE, std::ios::binary);
	if (!packageFile) {
		LOG("Could not read file [$]", PACKAGE_FILE);
		return nullptr;
	}

	packageFile.seekg(assetsMetadata[fontFile].offset);
	std::vector<char> fontData(assetsMetadata[fontFile].size);

	if (!packageFile.read(fontData.data(), fontData.size())) {
		std::cerr << "Failed to read font data from package!" << std::endl;
		return nullptr;
	}

	// Load font from memory
	if (!font.loadFromMemory(fontData.data(), fontData.size())) {
		std::cerr << "Failed to load font from memory!" << std::endl;
		return nullptr;
	}
	packageFile.close();
	return std::make_shared<sf::Font>(font);
}