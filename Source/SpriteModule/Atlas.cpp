#include "Atlas.hpp"
#include <fstream>
#include <sstream>
#include <optional>
#include "Sprite.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <Common/Modules.hpp>

namespace {
	const std::string X = "x";
	const std::string Y = "y";
	const std::string WIDTH = "width";
	const std::string HEIGHT = "height";
	const std::string ATLAS_PATH = "atlasPath";
	const std::string IS_LOOPING = "isLooping";
	const std::string RENDER_DURATION = "renderDuration";
}

bool Atlas::initialize(const std::string& configFilePath) 
{
	//load atlasPath and rects
	if (!parseConfigFile(configFilePath))
		return false;

	//load atlas texture
	m_atlasTexture = std::make_shared<sf::Texture>();
	if (!m_atlasTexture->loadFromFile(m_atlasPath))
		return false;

	return true;
	
}
bool Atlas::parseConfigFile(const std::string& configFilePath) //works
{
	//init config file
	Modules::Config->addFile(configFilePath);
	const ConfigFile& walkingAnimation = Modules::Config->getFile(configFilePath);

	bool anyTextureAdded = false;
	std::vector<std::string> m_configValues = { ATLAS_PATH, IS_LOOPING, RENDER_DURATION };
	std::vector<std::string> m_rectValues = { X, Y, WIDTH, HEIGHT };

	//check all sections
	const auto& sections = walkingAnimation.getAllSections();
	for (const auto& sectionName : sections)
	{

		if (!walkingAnimation.isSectionPresent(sectionName))
			break;

		if (walkingAnimation.getSection(sectionName).areValuesPresent(m_configValues))
		{
			const ConfigSection& mySection = walkingAnimation.getSection(sectionName);

			//load atlas path
			m_atlasPath = mySection.getValue(ATLAS_PATH).getString();

			//load isLooping value 
			m_isLooping = mySection.getValue(IS_LOOPING).getBool();

			//load render duration
			m_renderDuration = mySection.getValue(RENDER_DURATION).getFloat();

		}
		else if (walkingAnimation.getSection(sectionName).areValuesPresent(m_rectValues))
		{
			//load rect infos
			const ConfigSection& mySection = walkingAnimation.getSection(sectionName);
			int32_t x = mySection.getValue(X).getInt32();
			int32_t y = mySection.getValue(Y).getInt32();
			int32_t width = mySection.getValue(WIDTH).getInt32();
			int32_t height = mySection.getValue(HEIGHT).getInt32();

			//set to map
			m_texturesRect[sectionName] = sf::IntRect(x, y, width, height);
			anyTextureAdded = true;
		}
	}

	return anyTextureAdded;
}



sf::IntRect Atlas::getTextureRect(const std::string& textureName) const
{
	auto textureRect = m_texturesRect.find(textureName);

	if (textureRect != m_texturesRect.end())
	{
		return textureRect->second;
	}
	return sf::IntRect();
}

