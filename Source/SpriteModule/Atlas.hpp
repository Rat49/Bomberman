#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <optional>

class Sprite;

class Atlas 
{
public:
	Atlas() = default;

	bool initialize(const std::string& configFilePath);
	std::shared_ptr<Sprite> initializeSprite(const std::string& textureName) const;
	bool parseConfigFile(const std::string& configFile);

	sf::IntRect getTextureRect(const std::string& textureName) const;
	const std::unordered_map<std::string, sf::IntRect>& getAllTextureRects() const { return m_texturesRect;}

	std::shared_ptr<sf::Texture> getTexture() const { return m_atlasTexture; }
	float getRenderDuration() const { return m_renderDuration; }
	bool isLooping() const { return m_isLooping; }

private:
	std::shared_ptr<sf::Texture> m_atlasTexture;
	std::unordered_map<std::string, sf::IntRect> m_texturesRect;
	
	std::string m_baseFrameName = "Walk";
	std::string m_atlasPath;
	float m_renderDuration;
	bool m_isLooping;

};