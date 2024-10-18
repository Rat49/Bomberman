#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <optional>

class Sprite;

class Atlas 
{
private:
	bool parseDescriptionFile(const std::string& descriptionFile);

public:
	Atlas() = default;

	bool initialize(const std::string& path, const std::string& descriptionFile);
	std::shared_ptr<Sprite> initializeSprite(const std::string& textureName) const;

	std::optional<sf::IntRect> getTextureRect(const std::string& textureName) const;
	std::shared_ptr<sf::Texture> getTexture() const;

private:
	std::shared_ptr<sf::Texture> m_atlasTexture;
	std::unordered_map<std::string, sf::IntRect> m_texturesRect;

};