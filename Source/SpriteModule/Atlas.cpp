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
	ConfigFile configFile(configFilePath, true);
	Modules::Config->addFile(configFile);


	//load atlas path
	if (!configFile.isSectionPresent("AnimationConfig"))
		return false;
	if (!configFile.getSection("AnimationConfig").isValuePresent("atlasPath"))
		return false;
	m_atlasPath = configFile.getSection("AnimationConfig").getValue("atlasPath").getString();


	//load isLooping value
	if (!configFile.getSection("AnimationConfig").isValuePresent("isLooping"))
		return false;
	m_isLooping = configFile.getSection("AnimationConfig").getValue("isLooping").getBool();

	//load render duration
	if (!configFile.getSection("AnimationConfig").isValuePresent("renderDuration"))
		return false;
	m_renderDuration = configFile.getSection("AnimationConfig").getValue("renderDuration").getFloat();


	//load rects
	int frameIndex = 1;
	bool anyTextureAdded = false;

	while (true)
	{
		std::string sectionName = m_baseFrameName + std::to_string(frameIndex);
		const auto& section = configFile.getSection(sectionName);

		if (!configFile.isSectionPresent(sectionName))
			break;

		if (section.isValuePresent("x") &&
			section.isValuePresent("y") &&
			section.isValuePresent("width") &&
			section.isValuePresent("height"))
		{

			//take config values
			int32_t x = section.getValue("x").getInt32();
			int32_t y = section.getValue("y").getInt32();
			int32_t width = section.getValue("width").getInt32();
			int32_t height = section.getValue("height").getInt32();
			
			//set to map
			m_texturesRect[sectionName] = sf::IntRect(x, y, width, height);
			anyTextureAdded = true;
		}
		else
			return false;

		frameIndex++;
	}
	return anyTextureAdded;
}


//getters
sf::IntRect Atlas::getTextureRect(const std::string& textureName) const
{
	auto textureRect = m_texturesRect.find(textureName);

	if (textureRect != m_texturesRect.end())
	{
		return textureRect->second;
	}
	return sf::IntRect();
}



//i will try to avoid Sprite class for now
std::shared_ptr<Sprite> Atlas::initializeSprite(const std::string& textureName) const
{
	auto it = m_texturesRect.find(textureName);

	if (it != m_texturesRect.end())
	{
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
		//sprite->initialize(textureName, *this);
		return sprite;
	}
	return nullptr;
}
