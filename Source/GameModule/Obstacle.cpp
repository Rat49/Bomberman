#include "GameModule/Obstacle.hpp"
#include "Common/Modules.hpp"
#include <random>
#include <set>
#include <utility>
#include <Common/Logs.hpp>

Obstacle::Obstacle(ObstacleType type, sf::Vector2f position, bool hasKeyOrGate) : obstacleType(type), obstaclePosition(position), obstacleHasKeyOrGate(hasKeyOrGate)
{
	idleBreakableObstacleAnimID = Modules::Sprite->createAnimation("../../Data/Config/BreakableObstacle.ini");
	obstacleDestructionAnimID = Modules::Sprite->createAnimation("../../Data/Config/ObstacleDestruction.ini");

	currentAnimation = idleBreakableObstacleAnimID;
	getCurrentAnimation()->setPosition((float)position.x, (float)position.y);
	getCurrentAnimation()->Play();

	isExploded = false;

	collision.setObjectParent(this);

	collisionBox = std::make_unique<CollisionComponent>();

	collisionBox->setObjectParent(this);

	collisionBox->setRectangleProperties(sf::Vector2f((float)getPosition().x, (float)getPosition().y), sf::Vector2f(60.0f, 60.0f));
}

void Obstacle::changeAnim(sf::Vector2f obsPos)
{
	getCurrentAnimation()->Stop();
	if (auto animation = Modules::Sprite->getAnimation(obstacleDestructionAnimID))
	{ 
		currentAnimation = obstacleDestructionAnimID;
		animation->setPosition(obsPos);
		animation->Play();
	}
}

sf::Vector2f Obstacle::getPosition() const
{
	return obstaclePosition;
}

ObstacleType Obstacle::getType() const
{
	return obstacleType;
}

bool Obstacle::hasKeyOrGate() const
{
	return obstacleHasKeyOrGate;
}

void Obstacle::setHasKeyOrGate(bool value)
{
	obstacleHasKeyOrGate = value;
}

bool Obstacle::isValidUnbreakablePosition(const sf::Vector2f& position)
{
	return (int32_t)position.x % 2 == 0 && (int32_t)position.y % 2 == 0;;
}

std::shared_ptr<Animation> Obstacle::getCurrentAnimation() const
{
	return Modules::Sprite->getAnimation(currentAnimation);
}
