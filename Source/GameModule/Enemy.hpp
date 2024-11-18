#pragma once

#include <SFML/System.hpp>
#include <vector>
#include "GameModule/Obstacle.hpp"

enum class EnemyType {
	Basic,
	Chasing,
	BombThrower,
	Speedy,
	Suicidal,
	Flying,
	Shielded
};

class Enemy
{
public:
	Enemy(EnemyType type, sf::Vector2i spawnPosition, const std::vector<sf::Vector2i>& patrollingPoints = {});

	EnemyType getType() const;

	sf::Vector2i getSpawnPosition() const;

	const std::vector<sf::Vector2i>& getPatrollingPoints() const;

	// Static method for generating enemies
	static std::vector<Enemy> generateEnemies(int width, int height, int enemyCount, const sf::Vector2i& playerStartPosition, int gameLevel, const std::vector<Obstacle>& obstacles);

private:
	EnemyType enemyType;
	sf::Vector2i spawnPosition;
	std::vector<sf::Vector2i> patrollingPoints;
};
