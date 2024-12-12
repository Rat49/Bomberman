#include "GameModule/Bomb.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Logs.hpp"

Bomb::Bomb()
{
	collision.setParent(static_cast<void*>(this));

	collisionBox = std::make_unique<CollisionComponent>();

	collisionBox->setParent(this);

	collisionBox->setRectangleProperties(position, sf::Vector2f(gridSize - 8.0f, gridSize - 8.0f));
}

bool Bomb::Initialize(const sf::Vector2f& newPosition, float newExplosionRadius, float newTimer)
{
	bombIdleID = Modules::Sprite->createAnimation("../../Data/Config/BombIdleAnimation.ini");
	bombUpID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionUpAnimation.ini");
	bombDownID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionDownAnimation.ini");
	bombLeftID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionLeftAnimation.ini");
	bombRightID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionRightAnimation.ini");
	bombCenterID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionCenterAnimation.ini");

	currentAnimation = bombIdleID;
	sf::Vector2f pos = alignToGrid(newPosition);

	if (const auto& animation = Modules::Sprite->getAnimation(bombIdleID))
	{
		getCurrentAnimation()->setPosition(pos);
		animation->Play();
	}
	else
	{
		LOG("Failed to retrieve animation with ID: " + std::to_string(bombIdleID));
	}

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

	if (newTimer < 2.0f)
	{
		LOG("Timer must be at least 2.");
		return false;
	}

	this->position = pos;
	this->explosionRadius = newExplosionRadius;
	this->timer = newTimer;

	return true;
}

// Bomb update
void Bomb::update(float deltaTime)
{
	if (exploded)
	{
		explosionTimer -= deltaTime;
		if (explosionTimer <= 0.0f)
		{
			animExploded = true;
		}
	}

	timer -= deltaTime;
	if (timer <= 0.0f)
	{
		explode();
	}
}

// Drawing a bomb
void Bomb::draw(sf::RenderWindow& window)
{
	if (!Modules::Sprite->getAnimation(bombIdleID)->isPlaying())
		exploded = true;

	if (canChangeObstacleAnim)
	{
		for (auto& [obstacle, pos] : obstaclesHit)
		{
			if (obstacle)
			{
				obstacle->changeAnim(pos);
			}
		}
		canChangeObstacleAnim = false;
	}

	// Draws a bomb if it hasn't exploded
	if (!exploded)
	{
		if (auto animation = Modules::Sprite->getAnimation(bombIdleID))
		{
			window.draw(*animation);
		}
	}
	// Draws an explosion
	else if(exploded)
	{
		animExplosionStart = true;

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
		
		sf::Vector2f animPos;

		for (const auto& direction : directions)
		{
			int32_t animationID = getExplosionAnimationID(direction);
			animPos = directionToPosition(direction);
			if (auto animation = Modules::Sprite->getAnimation(animationID))
			{
				sf::Vector2f pos = alignToGrid(position + (animPos * explosionRadius));
				animation->setPosition(pos);
				window.draw(*animation);
			}
		}

		// Draw the center of the explosion
		if (auto animation = Modules::Sprite->getAnimation(bombCenterID))
		{
			sf::Vector2f pos = alignToGrid(position);
			animation->setPosition(pos);
			window.draw(*animation);
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
	if (animExplosionStart) return;

	auto animation = Modules::Sprite->getAnimation(bombIdleID);
	animation->Stop();

	int32_t animationID = getExplosionAnimationID(sf::Vector2f(-1, 0));
	currentAnimation = animationID;
	if (animation = Modules::Sprite->getAnimation(bombCenterID))
	{
		animation->setPosition(sf::Vector2f(64.0f, 64.0f));
		animation->Play();
	}

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
}

// Method about what will happen when there is an explosion
void Bomb::explosionEffect(const sf::Vector2f& direction)
{
	sf::Vector2f endPoint;

	sf::Vector2f newDirection = directionToPosition(direction);
	sf::Vector2f alignPos = alignToGrid(position);
	sf::Vector2f directionAndPosition = alignPos + newDirection;

	auto hitResults = Modules::Physics->rayCastAll(position, newDirection, 1.0f);
    Obstacle* hitObstacle;
	for (const auto& [obj, pos] : hitResults)
	{
		LOG("Collision detected! Position: $ $", pos.x, pos.y);

		hitObstacle = static_cast<Obstacle*>(obj->getParent());
		if (hitObstacle)
		{
			canChangeObstacleAnim = true;
            obstaclesHit.push_back(std::make_pair(hitObstacle, directionAndPosition));
			hitObstacle->isExploded = true;
		}
	}

	// Activation of direction animation
	int32_t animationID = getExplosionAnimationID(direction);
	currentAnimation = animationID;
	if (auto animation = Modules::Sprite->getAnimation(animationID))
	{
		animation->setPosition(directionAndPosition);
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

	return 0;
}

sf::Vector2f Bomb::directionToPosition(sf::Vector2f newDirection)
{
	sf::Vector2f dir = sf::Vector2f(newDirection.x * 64.0f, newDirection.y * 64.0f);

	return dir;
}

sf::Vector2f Bomb::alignToGrid(const sf::Vector2f& newPosition)
{
	float alignedX = std::floor(newPosition.x / gridSize) * gridSize;
	float alignedY = std::floor(newPosition.y / gridSize) * gridSize;
	return { alignedX, alignedY };
}

Bomb::~Bomb() {}
