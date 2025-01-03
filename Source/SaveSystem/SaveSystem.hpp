#pragma once

#include "BaseModule/BaseModule.hpp"
#include <string>
#include <unordered_map>

class SaveSystem : public BaseModule
{
public:
    /**
    * Saves the provided data map to a file in the Save folder.
    *
    * @param fileName The name of the save file (without extension).
    * @param dataMap A map of key-value pairs representing game data to be saved.
    * @return True if the data is saved successfully; otherwise, false.
    *
    * This method serializes the data map into a string format where each key-value
    * pair is separated by a delimiter ('|'). The serialized string is then encrypted
    * and written to a binary file in the designated Save folder.
    */

    bool saveGameData(const std::string& fileName, const std::unordered_map<std::string, std::string>& dataMap);


    /**
     * Loads data from the specified file and populates the provided map.
     *
     * @param fileName The name of the save file (without extension).
     * @param dataMap A map where the loaded key-value pairs will be stored.
     * @return True if the data is loaded successfully; otherwise, false.
     *
     * This method reads and decrypts the binary data from the specified save file.
     * The data is then deserialized into key-value pairs and stored in the provided map.
     */

    bool loadGameData(const std::string& fileName, std::unordered_map<std::string, std::string>& dataMap);


    void terminate() override;

private:
    /**
    * Ensures the specified folder exists, creates it if necessary.
    *
    * @param folderPath The path of the folder to check or create.
    * @return True if the folder exists or is successfully created; otherwise, false.
    *
    * This method uses the standard filesystem library to verify if the folder exists.
    * If it does not exist, it attempts to create the folder. Any errors during the
    * creation process are logged.
    */

    bool createSaveFolder(const std::string& folderPath);
};
