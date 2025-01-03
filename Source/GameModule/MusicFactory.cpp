#include "MusicFactory.hpp"
#include "SoundSystem/SoundSystem.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <list>

namespace
{
const std::string TYPE = "type";
const std::string PATH = "path";
}

void MusicFactory::loadAllMusic(const std::string& path)
{
    const auto& configFile = Modules::Config->getFile(path);

    const auto& sections = configFile.getAllSections();

    for (const auto& sectionName : sections)
    {
        auto& section = configFile.getSection(sectionName);

        if (section.areValuesPresent({PATH, TYPE}))
        {
            int32_t type      = section.getValue(TYPE).getInt32();
            auto&   soundPath = section.getValue(PATH).getString();

            Modules::Sounds->addMusic(type, soundPath);
        }
        else
        {
            LOG("Failed to load music ($)", sectionName);
        }
    }
}

void MusicFactory::loadAllSounds(const std::string& path)
{
    const auto& configFile = Modules::Config->getFile(path);

    const auto& sections = configFile.getAllSections();

    for (const auto& sectionName : sections)
    {
        auto& section = configFile.getSection(sectionName);
        if (section.isValuePresent({TYPE}))
        {
            int32_t type = section.getValue(TYPE).getInt32();
            auto& musicPath = section.getValue(PATH).getString();

            Modules::Sounds->addSound(type, musicPath);
        }
        else
        {
            LOG("Failed to load sound ($)", sectionName);
        }
    }
}
