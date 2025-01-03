#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <unordered_map>

class Atlas
{
public:
    Atlas() = default;

    bool initialize(const std::string& configFilePath);
    bool parseConfigFile(const std::string& configFile);

    sf::IntRect                                         getTextureRect(const std::string& textureName) const;
    const std::unordered_map<std::string, sf::IntRect>& getAllTextureRects() const
    {
        return m_texturesRect;
    }

    std::shared_ptr<sf::Texture> getAtlasTexture() const
    {
        return m_atlasTexture;
    }
    float getRenderDuration() const
    {
        return m_renderDuration;
    }
    bool isLooping() const
    {
        return m_isLooping;
    }

private:
    std::shared_ptr<sf::Texture>                 m_atlasTexture;
    std::unordered_map<std::string, sf::IntRect> m_texturesRect;

    std::string m_atlasPath;
    float       m_renderDuration;
    bool        m_isLooping;
};