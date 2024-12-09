#pragma once

#include <SFML/System.hpp>
#include <vector>
#include "GameModule/Obstacle.hpp"

enum class EnemyType
{
	Basic,
	Medium,
	Hard
};

class Enemy : public sf::Sprite
{
public:
	Enemy(EnemyType type, sf::Vector2i spawnPosition); // , const std::vector<sf::Vector2i>& patrollingPoints = {});

	EnemyType getType() const;

	sf::Vector2i getSpawnPosition() const;

	const std::vector<sf::Vector2i>& getPatrollingPoints() const;

private:
	EnemyType enemyType;
	sf::Vector2i spawnPosition;
	std::vector<sf::Vector2i> patrollingPoints;
};
