#include "PackageTool.hpp"
#include "Common/StringUtils.hpp"
#include <fstream>
#include <vector>
#include <filesystem>
#include "LogModule/LogManager.hpp"

namespace fs = std::filesystem;

namespace {
	const std::string BINARY_OUTPUT_FILE   = "bomberman.pkg";
	const std::string METADATA_OUTPUT_FILE = "bomberman.mtd";
	const std::string RELATIVE_ROOT_FOLDER = "Game/";
	const std::string CIPHER_KEY           = "VERYSECUREKEY";
	const std::string ASSETS_PATH          = "../../../../Assets";
	const std::string DEBUG_FOLDER_PATH    = "../../Debug/Bomberman";
	const std::string RELEASE_FOLDER_PATH  = "../../Release/Bomberman";
	const std::string FINAL_FOLDER_PATH    = "../../Final/Bomberman";
	const std::string PACKAGE_FOLDER       = "Package";
}

PackageTool::PackageTool()
{
	Logs = std::make_unique<LogManager>();
}

bool PackageTool::addToPackage(const std::string& filePath, PkgAsset& outPkgAsset, std::ostream& outputFile)
{
	std::streampos size;

	std::ifstream inputFile(filePath, std::ios::binary | std::ios::ate);
	if (!inputFile)
	{
		Logs->Log("File [$] could not be opened", filePath);
		return false;
	}

	size = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	if (!inputFile.read(buffer.data(), size))
	{
		Logs->Log("Error reading the file [$]", filePath);
		return false;
	}
	inputFile.close();

	outputFile.seekp(0, std::ios::end);

	std::vector<std::string> tokens;
	size_t tokensSize     = StringUtils::tokenize(filePath, '\\', tokens) - 1;
	std::string name      = RELATIVE_ROOT_FOLDER + tokens[tokensSize - 1] + '/' + tokens[tokensSize];
	outPkgAsset.assetName = name;
	outPkgAsset.size      = size;
	outPkgAsset.offset    = outputFile.tellp();

	outputFile.write(buffer.data(), size);

	return true;
}

bool PackageTool::createPackageFile()
{
	fs::create_directory(PACKAGE_FOLDER);

	fs::path dirPath(ASSETS_PATH);
	if (!fs::exists(dirPath))
	{
		Logs->Log("Folder [$] does not exist", dirPath);
		return false;
	}

	if (!fs::is_directory(dirPath))
	{
		Logs->Log("[$] is not a folder", dirPath);
		return false;
	}

	std::ofstream packageFile(PACKAGE_FOLDER + '/' + BINARY_OUTPUT_FILE, std::ios::binary | std::ios::trunc);
	if (!packageFile)
	{
		Logs->Log("Unable to open output file [$]", BINARY_OUTPUT_FILE);
		return false;
	}

	std::ofstream metadataFile(PACKAGE_FOLDER + '/' + METADATA_OUTPUT_FILE, std::ios::trunc);
	if (!metadataFile)
	{
		Logs->Log("Unable to open output file [$]", BINARY_OUTPUT_FILE);
		return false;
	}

	std::string toInsert = "";
	for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
		if (fs::is_regular_file(entry))
		{
			PkgAsset newPkgAsset = {};
			if (addToPackage(entry.path().string(), newPkgAsset, packageFile))
			{
				toInsert += newPkgAsset.assetName + ";" + std::to_string(newPkgAsset.size) + ";" + std::to_string(newPkgAsset.offset) + "\n";
			}
		}
	}

	StringUtils::cipherText(toInsert, CIPHER_KEY);
	metadataFile << toInsert;

	packageFile.close();
	metadataFile.close();

	for (const auto& targetDir : { DEBUG_FOLDER_PATH, RELEASE_FOLDER_PATH, FINAL_FOLDER_PATH })
	{
		if (fs::exists(targetDir))
		{
			fs::copy(PACKAGE_FOLDER, targetDir + '/' + PACKAGE_FOLDER, fs::copy_options::recursive | fs::copy_options::update_existing);
		}
		else
		{
			Logs->Log("Directory [$] does not exist", targetDir);
		}
	}

	Logs->Log("Package file created successfully!");

	return true;
}