#include "GameModule/Obstacle.hpp"
#include "Common/Modules.hpp"
#include <random>
#include <set>
#include <utility>

Obstacle::Obstacle() {}

Obstacle::Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate) : obstacleType(type), obstaclePosition(position), obstacleHasKeyOrGate(hasKeyOrGate)
{
	collision.setParent(static_cast<void*>(this));

	collisionBox = std::make_unique<CollisionComponent>();

	collisionBox->setParent(this);

	collisionBox->setRectangleProperties(sf::Vector2f((float)getPosition().x, (float)getPosition().y), sf::Vector2f(52.0f, 52.0f));
}

void Obstacle::draw(sf::RenderWindow& window, sf::Vector2f obsPos)
{
	obstacleDestructionAnimID = Modules::Sprite->createAnimation("../../Data/Config/ObstacleDestruction.ini");
	currentAnimation = obstacleDestructionAnimID;
	getCurrentAnimation()->setPosition(obsPos);
	if (auto animation = Modules::Sprite->getAnimation(obstacleDestructionAnimID))
	{ 
		animation->Play();
		window.draw(*animation);
	}
}

sf::Vector2i Obstacle::getPosition() const
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

bool Obstacle::isValidUnbreakablePosition(const sf::Vector2i& position)
{
	return position.x % 2 == 0 && position.y % 2 == 0;;
}

std::shared_ptr<Animation> Obstacle::getCurrentAnimation() const
{
	return Modules::Sprite->getAnimation(currentAnimation);
}
