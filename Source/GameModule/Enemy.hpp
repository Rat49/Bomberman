#pragma once

#include "SpriteModule/Animation.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include <SFML/System.hpp>
#include <vector>
#include "EventSystem/EventTypes.hpp"

enum class EnemyType
{
	Basic,
	Medium,
	Hard
};

class Enemy : public sf::Sprite, public CollisionObject
{
public:
	Enemy(EnemyType type, sf::Vector2f spawnPosition);

	EnemyType getType() const;

	sf::Vector2f getPosition() const;

	const std::vector<sf::Vector2i>& getPatrollingPoints() const;

	std::shared_ptr<Animation> getCurrentAnimation() const;

	void initializeDeath();

	bool isDead() const;

	CollisionComponent& getCollisionBox() const { return *collisionBox; }
    
	void setCallbackID(EventID enemyDeathID);

private:
	EnemyType enemyType;
	sf::Vector2f position;
	std::vector<sf::Vector2i> patrollingPoints;

	int32_t m_currentAnimationId = -1;
	int32_t m_deatAnimationId;
	int32_t m_leftAnimationId;
	int32_t m_rightAnimationId;

	std::unique_ptr<CollisionComponent> collisionBox;

	bool isEnemyDead = false;

	EventID m_enemyDeathID = -1;
};
