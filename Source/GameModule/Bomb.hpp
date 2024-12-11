#pragma once

#include "Common/Modules.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "GameModule/Obstacle.hpp"

class Bomb
{
public:
	Bomb();

	~Bomb();

	bool Initialize(const sf::Vector2f& newPosition, float newExplosionRadius, float newTimer);

	// Bomb update
	void update(float deltaTime);

	// Drawing a bomb
	void draw(sf::RenderWindow& window);

	// Explosion activation
	void explode();

	// Explosion status getter
	bool hasExploded() const { return exploded; }
	bool hasAnimExploded() const { return animExploded; }

	std::shared_ptr<Animation> getCurrentAnimation() const;

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

	CollisionRectangle& getCollision() { return collision; }

private:
	int32_t currentAnimation = -1;

	int32_t bombIdleID;
	int32_t bombUpID;
	int32_t bombDownID;
	int32_t bombLeftID;
	int32_t bombRightID;
	int32_t bombCenterID;

	std::unique_ptr<CollisionComponent> collisionBox;

	CollisionRectangle collision;

	float gridSize = 64.0f;

	// Bomb position
	sf::Vector2f position;

	// Explosion radius
	float explosionRadius;

	// Bomb before explosion timer
	float timer;

	// Explosion timer
	float explosionTimer = 1000000.0f;

	// Did the bomb explode
	bool exploded = false;
	bool animExploded = false;
	bool animExplosionStart = false;

	std::unordered_map<Obstacle*, sf::Vector2f> obstaclesHit;
	Obstacle* hitObstacle;
	bool canChangeObstacleAnim = false;

	// Method about what will happen when there is an explosion
	void explosionEffect(const sf::Vector2f& direction);

	int32_t getExplosionAnimationID(const sf::Vector2f& direction) const;

	sf::Vector2f alignToGrid(const sf::Vector2f& newPosition);

	sf::Vector2f directionToPosition(sf::Vector2f newDirection);
};
