#include "SaveSystem.hpp"
#include "Common/Logs.hpp"
#include "Common/StringUtils.hpp"
#include "FileWriter.hpp"
#include "FileReader.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace {
	const std::string ROOT_SAVE_FOLDER = "../../Save";
	const std::string FILE_EXTENSION = ".dat";
	const std::string CIPHER_KEY = "VERYSECUREKEY";
}

bool SaveSystem::createSaveFolder(const std::string& folderName)
{
	if (!fs::exists(folderName)) 
	{
		LOG("Folder doesn't exist, create it");
		if (!fs::create_directory(folderName)) 
		{
			LOG("Failed to create folder: [$]", folderName);
			return false;
		}
	}
	return true;
}

bool SaveSystem::saveGameData(const std::string& fileName, const std::unordered_map<std::string, std::string>& dataMap)
{
	//ensure the root folder exists
	if (!createSaveFolder(ROOT_SAVE_FOLDER))
		return false;

	//create file path
	const std::string filePath = ROOT_SAVE_FOLDER + '/' + fileName + FILE_EXTENSION;

	//open file for writing
    FileWriter writer;
	if (!writer.open(filePath))
	{
        LOG("Failed to opet file [$] for writing", filePath);
        return false;
	}

	//store data in string
	std::string serializedData;
	for (const auto& pair : dataMap)
	{
		serializedData += pair.first + "|" + pair.second + "|";
	}

	//encrypt data
    StringUtils::cipherText(serializedData, CIPHER_KEY);

	//write data to file
    writer.write(serializedData);
    writer.close();
	return true;
}

bool SaveSystem::loadGameData(const std::string& fileName, std::unordered_map <std::string, std::string>& dataMap)
{
	//create file path
	const std::string filePath = ROOT_SAVE_FOLDER + '/' + fileName + FILE_EXTENSION;

	//open file for reading
    FileReader reader;
	if (!reader.open(filePath))
	{
        LOG("Failed to open file [$] fro reading", filePath);
        return false;
	}

	//read data
    auto data = reader.readAll();

	//decrypt data
	StringUtils::cipherText(data, CIPHER_KEY);

	//splitting the data and storing it in the map
	std::vector<std::string> items;
	StringUtils::tokenize(data, '|', items);

	for (size_t i = 0; i < items.size(); i += 2)
	{
		if (i + 1 < items.size())
		{
			dataMap[items[i]] = items[i + 1];
		}
	}

	return true;

}

void SaveSystem::terminate()
{}
