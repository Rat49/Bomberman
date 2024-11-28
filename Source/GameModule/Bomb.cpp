#include "GameModule/Bomb.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <vector>

Bomb::Bomb()
{
	bombIdleID = Modules::Sprite->createAnimation("../../Data/Config/BombIdleAnimation.ini");
	bombUpID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionUpAnimation.ini");
	bombDownID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionDownAnimation.ini");
	bombLeftID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionLeftAnimation.ini");
	bombRightID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionRightAnimation.ini");
	bombCenterID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionCenterAnimation.ini");

	currentAnimation = bombIdleID;

	if (const auto& animation = Modules::Sprite->getAnimation(bombIdleID))
	{
		animation->Play();
	}
	else
	{
		LOG("Failed to retrieve animation with ID: " + std::to_string(bombIdleID));
		if (const auto& defaultAnim = Modules::Sprite->getAnimation(defaultAnimation))
		{
			defaultAnim->Play();
		}
		else
		{
			LOG("Failed to play default animation.");
		}
	}
}

bool Bomb::Initialize(const sf::Vector2f& newPosition, int32_t newExplosionRadius, float newTimer)
{
	if (newPosition.x < 2 || newPosition.y < 2)
	{
		LOG("Wrong position. The position of bomb on x and y must be greater than 2.");
		return false;
	}

	if (newExplosionRadius < 1)
	{
		LOG("Explosion Radius must be at least 1.");
		return false;
	}

	if (newTimer < 1.0f)
	{
		LOG("Timer must be at least 1.");
		return false;
	}

	this->position = newPosition;
	this->explosionRadius = newExplosionRadius;
	this->timer = newTimer;

	return true;
}

// Bomb update
void Bomb::update(float deltaTime)
{
	if (exploded) return;

	timer -= deltaTime;
	if (timer <= 0.0f)
	{
		explode();
	}
}

// Drawing a bomb
void Bomb::draw(sf::RenderWindow& window)
{
	// Draws a bomb if it hasn't exploded
	if (!exploded)
	{
		if (auto animation = Modules::Sprite->getAnimation(bombIdleID))
		{
			animation->setPosition(position);
			animation->Play();
		}
	}
	// Draws an explosion
	else
	{
		sf::Vector2f directions[] =
		{
			// Right
			{1, 0},
			// Left
			{-1, 0},
			// Down
			{0, 1},
			// Up
			{0, -1}
		};

		for (const auto& direction : directions)
		{
			int32_t animationID = getExplosionAnimationID(direction);
			if (auto animation = Modules::Sprite->getAnimation(animationID))
			{
				animation->Play();
			}
		}

		// Draw the center of the explosion
		if (auto animation = Modules::Sprite->getAnimation(bombCenterID))
		{
			animation->Play();
		}
	}
}

std::shared_ptr<Animation> Bomb::getCurrentAnimation() const
{
	return Modules::Sprite->getAnimation(currentAnimation);
}

// Explosion activation
void Bomb::explode()
{
	if (exploded) return;

	exploded = true;

	sf::Vector2f directions[] =
	{
		// Right
		{1, 0},
		// Left
		{-1, 0},
		// Down
		{0, 1},
		// Up
		{0, -1}
	};

	for (const auto& direction : directions)
	{
		explosionEffect(direction);
	}

	LOG("The bomb exploded at the position: $", position.x, ", $", position.y);
}

// Method about what will happen when there is an explosion
void Bomb::explosionEffect(const sf::Vector2f& direction)
{
	sf::Vector2f endPoint;
	const CollisionComponent* hitObject = Modules::Physics->rayCast(position, direction, explosionRadius, endPoint);

	if (hitObject)
	{
		// I will add something in Collision to mark if the object is destructable, or not?
		//if (hitObject-> check if object is destructable)
		//{
		//	LOG("The explosion destroyed the obstacle on: $", endPoint.x, ", $", endPoint.y);
		//	hitObject->destroy();
		//}
		//else
		//{
		//	LOG("The explosion stopped at an indestructible barrier at: $", endPoint.x, ", $", endPoint.y);
		//}
	}
	else
	{
		LOG("The explosion spread to: $", endPoint.x, ", $", endPoint.y);
	}

	// Activation of direction animation
	int32_t animationID = getExplosionAnimationID(direction);
	if (auto animation = Modules::Sprite->getAnimation(animationID))
	{
		animation->setPosition(position + direction * (float)explosionRadius);
		animation->Play();
	}
}


int32_t Bomb::getExplosionAnimationID(const sf::Vector2f& direction) const
{
	if (direction == sf::Vector2f{ 1, 0 }) return bombRightID; // Right
	if (direction == sf::Vector2f{ -1, 0 }) return bombLeftID; // Left
	if (direction == sf::Vector2f{ 0, 1 }) return bombDownID; // Down
	if (direction == sf::Vector2f{ 0, -1 }) return bombUpID;  // Up
	if (direction == sf::Vector2f{ 0, 0 }) return bombCenterID;  // Center
}

Bomb::~Bomb()
{

}
