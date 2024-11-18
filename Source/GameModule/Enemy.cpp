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

// Enemy generation
std::vector<Enemy> Enemy::generateEnemies(int width, int height, int enemyCount, const sf::Vector2i& playerStartPosition, int gameLevel, const std::vector<Obstacle>& obstacles)
{
	std::vector<Enemy> enemies;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);
	std::uniform_int_distribution<> typeDist(0, 6);

	// Based on the level, we get enemy types
	std::vector<EnemyType> availableTypes;
	switch (gameLevel) {
	case 1:
		availableTypes = { EnemyType::Basic };
		break;
	case 2:
		availableTypes = { EnemyType::Basic, EnemyType::Speedy };
		break;
	case 3:
		availableTypes = { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing };
		break;
	case 4:
		availableTypes = { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing, EnemyType::BombThrower };
		break;
	case 5:
		availableTypes = { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing, EnemyType::BombThrower, EnemyType::Suicidal };
		break;
	default:
		availableTypes = { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing, EnemyType::BombThrower, EnemyType::Suicidal, EnemyType::Flying, EnemyType::Shielded };
		break;
	}

	std::set<std::pair<int, int>> usedPositions;

	// Safety zone around the player 
	int safetyRadius = 3;
	for (int y = playerStartPosition.y - safetyRadius; y <= playerStartPosition.y + safetyRadius; ++y)
	{
		for (int x = playerStartPosition.x - safetyRadius; x <= playerStartPosition.x + safetyRadius; ++x)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				usedPositions.emplace(x, y);
			}
		}
	}

	// Add obstacles to the set of occupied positions
	for (const auto& obstacle : obstacles)
	{
		usedPositions.emplace(obstacle.getPosition().x, obstacle.getPosition().y);
	}

	int placedEnemies = 0;
	while (placedEnemies < enemyCount)
	{
		int x = distX(gen);
		int y = distY(gen);
		sf::Vector2i position(x, y);

		if (usedPositions.find({ x, y }) == usedPositions.end())
		{
			// Choose an enemy type from the available types
			EnemyType type = availableTypes[distX(gen) % availableTypes.size()];

			// Generate patrol points
			std::vector<sf::Vector2i> patrollingPoints;
			for (int i = 0; i < 3; ++i)
			{
				int patrolX = distX(gen);
				int patrolY = distY(gen);
				patrollingPoints.emplace_back(patrolX, patrolY);
			}

			enemies.emplace_back(type, position, patrollingPoints);
			usedPositions.emplace(x, y);
			++placedEnemies;
		}
	}
	return enemies;
}
