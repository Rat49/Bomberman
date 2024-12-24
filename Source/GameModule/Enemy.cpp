#include "GameModule/Enemy.hpp"
#include <random>
#include <set>
#include <utility>
#include "Common/Modules.hpp"
#include "SpriteModule/Animation.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "SpriteModule/Sprite.hpp"
#include "Common/Logs.hpp"
Enemy::Enemy(EnemyType type, sf::Vector2f spawnPosition) : enemyType(type), position(spawnPosition)
{
	// different animations for different enemies needs to be added
	switch (type)
	{
	case EnemyType::Basic:	
		m_rightAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomAnimationRight.ini");
		m_leftAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomAnimationLeft.ini");
		m_deatAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomDeathAnimation.ini");
		m_currentAnimationId = m_leftAnimationId;
		break;
	case EnemyType::Medium:
		m_rightAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomAnimationRight.ini");
		m_leftAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomAnimationLeft.ini");
		m_deatAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomDeathAnimation.ini");
		m_currentAnimationId = m_leftAnimationId;
		break;
	case EnemyType::Hard:
		m_rightAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomAnimationRight.ini");
		m_leftAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomAnimationLeft.ini");
		m_deatAnimationId = Modules::Sprite->createAnimation("../../Data/Config/BallomDeathAnimation.ini");
		m_currentAnimationId = m_leftAnimationId;
		break;
	default:
		break;
	}

	Modules::Sprite->getAnimation(m_currentAnimationId)->setPosition(spawnPosition);
	Modules::Sprite->getAnimation(m_currentAnimationId)->Play();

	
	collision.setObjectParent(this);

    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties(getPosition(), sf::Vector2f(64.0f, 64.0f));

    collisionBoxID = Modules::Physics->registerObject(collisionBox.get());

    Modules::Physics->addObject(collisionBox.get());
}

EnemyType Enemy::getType() const
{
	return enemyType;
}

sf::Vector2f Enemy::getPosition() const
{
	return position;
}

const std::vector<sf::Vector2i>& Enemy::getPatrollingPoints() const
{
	return patrollingPoints;
}

std::shared_ptr<Animation> Enemy::getCurrentAnimation() const
{
	return Modules::Sprite->getAnimation(m_currentAnimationId);
}

void Enemy::initializeDeath()
{
	if (!isEnemyDead)
	{
		Modules::Sprite->getAnimation(m_currentAnimationId)->Stop();
		m_currentAnimationId = m_deatAnimationId;
		Modules::Sprite->getAnimation(m_currentAnimationId)->Play();
		Modules::Sprite->getAnimation(m_currentAnimationId)->setPosition(position);
		isEnemyDead = true;
	}
}

bool Enemy::isDead() const
{
	if (Modules::Sprite->getAnimation(m_currentAnimationId)->isPlaying())
	{
		return false;
	}
	return true;
}