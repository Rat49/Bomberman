#include "PackageManager.hpp"
#include "Common/Logs.hpp"
#include "Common/StringUtils.hpp"
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace {
	const std::string BINARY_OUTPUT_FILE   = "../../Source/AssetManager/bomberman.pkg";
	const std::string METADATA_OUTPUT_FILE = "../../Source/AssetManager/bomberman.mtd";
	const std::string RELATIVE_ROOT_FOLDER = "Game/";
	const std::string CIPHER_KEY           = "VERYSECUREKEY";
}

bool PackageManager::loadToPackage(const std::string& filePath, PkgAsset& pkgAsset, std::ostream& outputFile)
{
	std::streampos size;

	std::ifstream inputFile(filePath, std::ios::binary | std::ios::ate);
	if (!inputFile)
	{
		LOG("File [$] could not be opened", filePath);
		return false;
	}

	size = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);
	
	std::vector<char> buffer(size);
	if (!inputFile.read(buffer.data(), size))
	{
		LOG("Error reading the file [$]", filePath);
		return false;
	}
	inputFile.close();

	outputFile.seekp(0, std::ios::end);

	std::vector<std::string> tokens;
	size_t tokensSize  = StringUtils::tokenize(filePath, '\\', tokens) - 1;
	std::string name   = RELATIVE_ROOT_FOLDER + tokens[tokensSize - 1] + '/' + tokens[tokensSize];
	pkgAsset.assetName = name;
	pkgAsset.size      = size;
	pkgAsset.offset    = outputFile.tellp();

	LOG("[$] = [$]:[$]",pkgAsset.assetName, pkgAsset.size, pkgAsset.offset);

	outputFile.write(buffer.data(), size);

	return true;
}

bool PackageManager::createPackageFile(const std::string folderPath)
{
	fs::path dirPath(folderPath);
	if (!fs::exists(dirPath))
	{
		LOG("Folder [$] does not exist", folderPath);
		return false;
	}

	if (!fs::is_directory(dirPath))
	{
		LOG("[$] is not a folder", folderPath);
		return false;
	}

	std::ofstream packageFile(BINARY_OUTPUT_FILE, std::ios::binary | std::ios::trunc);
	if (!packageFile)
	{
		LOG("Unable to open output file [$]", BINARY_OUTPUT_FILE);
		return false;
	}

	std::ofstream metadataFile(METADATA_OUTPUT_FILE, std::ios::trunc);
	if (!metadataFile)
	{
		LOG("Unable to open output file [$]", BINARY_OUTPUT_FILE);
		return false;
	}

	for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
		if (fs::is_regular_file(entry))
		{
			PkgAsset newPkgAsset = {};
			if (loadToPackage(entry.path().string(), newPkgAsset, packageFile))
			{
				std::string toInsert = newPkgAsset.assetName + ";" + std::to_string(newPkgAsset.size) + ";" + std::to_string(newPkgAsset.offset) + "\n";
				StringUtils::cipherText(toInsert, CIPHER_KEY);
				metadataFile << toInsert;
			}
		}
	}

	packageFile.close();
	metadataFile.close();

	return true;
}