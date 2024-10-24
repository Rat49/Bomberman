#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <optional>

namespace {
	const std::string X = "x";
	const std::string Y = "y";
	const std::string WIDTH = "width";
	const std::string HEIGHT = "height";
	const std::string ATLAS_PATH = "atlasPath";
	const std::string IS_LOOPING = "isLooping";
	const std::string RENDER_DURATION = "renderDuration";
}

class Atlas 
{
public:
	Atlas() = default;

	bool initialize(const std::string& configFilePath);
	bool parseConfigFile(const std::string& configFile);

	sf::IntRect getTextureRect(const std::string& textureName) const;
	const std::unordered_map<std::string, sf::IntRect>& getAllTextureRects() const { return m_texturesRect;}

	std::shared_ptr<sf::Texture> getAtlasTexture() const { return m_atlasTexture; }
	float getRenderDuration() const { return m_renderDuration; }
	bool isLooping() const { return m_isLooping; }

private:
	std::shared_ptr<sf::Texture> m_atlasTexture;
	std::unordered_map<std::string, sf::IntRect> m_texturesRect;
	
	std::string m_atlasPath;
	float m_renderDuration;
	bool m_isLooping;

	std::vector<std::string> m_rectValues = {X, Y, WIDTH, HEIGHT};
	std::vector<std::string> m_configValues = {ATLAS_PATH, IS_LOOPING, RENDER_DURATION};

};