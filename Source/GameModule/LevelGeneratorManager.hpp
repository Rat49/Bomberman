#pragma once

#include "LevelGenerator.hpp"
#include "LevelConfig.hpp"
#include <string>

class LevelGeneratorManager
{
public:

	LevelGeneratorManager() = default;

	bool initialize(const std::string& configPath);

	bool createLevel(uint32_t levelId);

	void drawLevel(sf::RenderTarget& target) const;

private:

	LevelConfig m_levelConfig;

	std::unordered_map<int32_t, LevelConfig> m_levelConfigData;

	std::unique_ptr<LevelGenerator> m_levelGenerator;

};

