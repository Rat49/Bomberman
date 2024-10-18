#include "Atlas.hpp"
#include <fstream>
#include <sstream>
#include <optional>
#include "Sprite.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <Common/Modules.hpp>


bool Atlas::initialize(const std::string& atlasPath, const std::string& configFilePath) //works
{
	//load atlas
	m_atlasTexture = std::make_shared<sf::Texture>();
	if (!m_atlasTexture->loadFromFile(atlasPath))
		return false;


	//load rects
	if (!parseDescriptionFile(configFilePath))
		return false;


	return true;
}
bool Atlas::parseDescriptionFile(const std::string& configFilePath) //works
{
	//init config file
	ConfigFile configFile(configFilePath, true);
	Modules::Config->addFile(configFile);

	//go through all sections
	int frameIndex = 1;
	bool anyTextureAdded = false;
	while (true)
	{
		std::string sectionName = "Walk"+ std::to_string(frameIndex); //for test
		if (!configFile.isSectionPresent(sectionName))
			break;

		if (configFile.getSection(sectionName).isValuePresent("x") &&
			configFile.getSection(sectionName).isValuePresent("y") &&
			configFile.getSection(sectionName).isValuePresent("width") &&
			configFile.getSection(sectionName).isValuePresent("height"))
		{

			//take values for animation
			int32_t x = configFile.getSection(sectionName).getValue("x").getInt32();
			int32_t y = configFile.getSection(sectionName).getValue("y").getInt32();
			int32_t width = configFile.getSection(sectionName).getValue("width").getInt32();
			int32_t height = configFile.getSection(sectionName).getValue("height").getInt32();

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

std::shared_ptr<Sprite> Atlas::initializeSprite(const std::string& textureName) const
{
	auto it = m_texturesRect.find(textureName);
	
	if (it != m_texturesRect.end())
	{
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
		sprite->initialize(textureName, *this);
		return sprite;
	}
	return nullptr;
}

std::optional<sf::IntRect> Atlas::getTextureRect(const std::string& textureName) const
{
	auto textureRect = m_texturesRect.find(textureName);

	if (textureRect != m_texturesRect.end())
	{
		return textureRect->second;
	}
	return std::nullopt;
}

std::shared_ptr<sf::Texture> Atlas::getTexture() const
{
	return m_atlasTexture;
}

