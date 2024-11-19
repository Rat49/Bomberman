#include "GameModule/Enemy.hpp"
#include <random>
#include <set>
#include <utility>

Enemy::Enemy(EnemyType type, sf::Vector2i spawnPosition, const std::vector<sf::Vector2i>& patrollingPoints) : enemyType(type), spawnPosition(spawnPosition), patrollingPoints(patrollingPoints) {}

EnemyType Enemy::getType() const
{
	return enemyType;
}

sf::Vector2i Enemy::getSpawnPosition() const
{
	return spawnPosition;
}

const std::vector<sf::Vector2i>& Enemy::getPatrollingPoints() const
{
	return patrollingPoints;
}
