#pragma once

#include <SFML/System.hpp>
#include <vector>
#include "GameModule/Obstacle.hpp"
#include "SpriteModule/Animation.hpp"

enum class EnemyType
{
	Basic,
	Medium,
	Hard
};

class Enemy : public sf::Sprite
{
public:
	Enemy(EnemyType type, sf::Vector2f spawnPosition); // , const std::vector<sf::Vector2i>& patrollingPoints = {});

	EnemyType getType() const;

	sf::Vector2f getPosition() const;

	const std::vector<sf::Vector2i>& getPatrollingPoints() const;

	std::shared_ptr<Animation> getCurrentAnimation() const;

	void initializeDeath();

	bool isDead() const;

private:
	EnemyType enemyType;
	sf::Vector2f position;
	std::vector<sf::Vector2i> patrollingPoints;

	int32_t m_currentAnimationId = -1;
	int32_t m_deatAnimationId;
	int32_t m_leftAnimationId;
	int32_t m_rightAnimationId;

	bool isEnemyDead = false;
};
