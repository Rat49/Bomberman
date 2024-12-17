#pragma once

#include <vector>
#include <memory>

class Enemy;
class Obstacle;
class Gate;
class Key;
class Booster;

enum class GameLevelType
{
	Easy = 1,
	Medium = 2,
	Hard = 3
};

struct LevelConfigs
{
	GameLevelType levelType;
	int32_t enemyCount;
	int32_t breakableCount;
	int32_t boostersCount;
};

struct GeneratedElements
{
	mutable std::vector<std::shared_ptr<Enemy>> enemies;
	mutable std::vector<std::shared_ptr<Obstacle>> obstacles;
	std::vector<std::shared_ptr<Gate>> gates;
	std::vector<std::shared_ptr<Key>> keys;
	std::vector<std::shared_ptr<Booster>> boosters;
};

