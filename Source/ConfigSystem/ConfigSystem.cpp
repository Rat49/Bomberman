#include "ConfigSystem.hpp"
#include <iostream>

const ConfigFile& ConfigSystem::getFile(const std::string& configFile) const
{
    auto it = configFiles.find(configFile);
    if (it != configFiles.end())
    {
        return it->second;
    }

    // I can add here else -> addFile but I don't know if I should
    static const ConfigFile defaltValue(configFile);
    return defaltValue;
}

void ConfigSystem::addFile(const std::string& configFile)
{
    if (!isFilePresent(configFile))
    {
        ConfigFile newFile(configFile);
        parser.parse(newFile);
        configFiles[newFile.getName()] = newFile;
    }
}

void ConfigSystem::removeFile(const std::string& configFile)
{
    configFiles.erase(configFile);
}

bool ConfigSystem::isFilePresent(const std::string& configFile) const
{
    return configFiles.find(configFile) != configFiles.end();
}

bool ConfigSystem::isSectionPresent(const std::string& configFile, const std::string& sectionName) const
{
    if (isFilePresent(configFile))
    {
        auto it = configFiles.find(configFile);
        return it->second.isSectionPresent(sectionName);
    }
    return false;
}

bool ConfigSystem::isValuePresent(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const
{
    if (isSectionPresent(configFile, sectionName))
    {
        auto  it  = configFiles.find(configFile);
        auto& it2 = it->second.getSection(sectionName);
        return it2.isValuePresent(valueName);
    }
    return false;
}

bool ConfigSystem::areValuesPresent(const std::string&              configFile,
                                    const std::string&              sectionName,
                                    const std::vector<std::string>& keys) const
{
    for (const auto& key : keys)
    {
        if (!isValuePresent(configFile, sectionName, key))
            return false;
    }
    return true;
}

const ConfigValue& ConfigSystem::getValue(const std::string& configFile,
                                          const std::string& sectionName,
                                          const std::string& valueName) const
{
    if (isValuePresent(configFile, sectionName, valueName))
    {
        auto  it  = configFiles.find(configFile);
        auto& it2 = it->second.getSection(sectionName);
        return it2.getValue(valueName);
    }
    else
    {
        static const ConfigValue defaultValue;
        return defaultValue;
    }
}

void ConfigSystem::setValue(const std::string& configFile,
                            const std::string& sectionName,
                            const std::string& valueName,
                            const std::string& value)
{
    if (isFilePresent(configFile))
    {
        auto it = configFiles.find(configFile);
        it->second.addToSection(sectionName, valueName, value);
    }
}

void ConfigSystem::terminate()
{
}
