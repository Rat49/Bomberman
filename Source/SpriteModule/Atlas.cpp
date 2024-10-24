#include "Atlas.hpp"
#include <fstream>
#include <sstream>
#include <optional>
#include "Sprite.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <Common/Modules.hpp>


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

	//check all sections
	const auto& sections = walkingAnimation.getAllSections();
	for (const auto& sectionName : sections)
	{

		if (!walkingAnimation.isSectionPresent(sectionName))
			break;

		if (walkingAnimation.getSection(sectionName).areValuesPresent({ "atlasPath", "isLooping", "renderDuration" }))
		{
			const ConfigSection& mySection = walkingAnimation.getSection(sectionName);

			//load atlas path
			m_atlasPath = mySection.getValue("atlasPath").getString();

			//load isLooping value 
			m_isLooping = mySection.getValue("isLooping").getBool();

			//load render duration
			m_renderDuration = mySection.getValue("renderDuration").getFloat();

		}
		else if (walkingAnimation.getSection(sectionName).areValuesPresent({ "x", "y", "width", "height" }))
		{
			//load rect infos
			const ConfigSection& mySection = walkingAnimation.getSection(sectionName);
			int32_t x = mySection.getValue("x").getInt32();
			int32_t y = mySection.getValue("y").getInt32();
			int32_t width = mySection.getValue("width").getInt32();
			int32_t height = mySection.getValue("height").getInt32();

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

