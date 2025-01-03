#pragma once

#include "Common/Modules.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "GameModule/Obstacle.hpp"
//#include "GameModule/PlayerCharacter.hpp"
#include "CollisionModule/CollisionObject.hpp"


class Bomb : public CollisionObject
{
public:
	Bomb();

	~Bomb();

	bool Initialize(const sf::Vector2f& newPosition, float newExplosionRadius, float newTimer);

	// Bomb update
    void update(float deltaTime, bool canDetonate);

	// Drawing a bomb
	void draw(sf::RenderWindow& window);

	// Explosion activation
	void explode();

	// When player can remotely detonate (picked booster) and click on key happened
	void setTimer(int32_t inc);

	// Explosion status getter
	bool hasExploded() const { return exploded; }
	bool hasAnimExploded() const { return animExploded; }

	std::shared_ptr<Animation> getCurrentAnimation() const;

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

private:
	int32_t currentAnimation = -1;

	int32_t bombIdleID;
	int32_t bombUpID;
	int32_t bombDownID;
	int32_t bombLeftID;
	int32_t bombRightID;
	int32_t bombCenterID;

	std::unique_ptr<CollisionComponent> collisionBox;

	float gridSize = 64.0f;

	// Bomb position
	sf::Vector2f position;

	// Explosion radius
	float explosionRadius = 1.0f;

	// Bomb before explosion timer
	float timer;

	// Explosion timer
	float explosionTimer = 1000000.0f;

	// Detonate cool down
    float detonateCooldown = 500000.0f;

	// Did the bomb explode
	bool exploded = false;
	bool animExploded = false;

	// If true that means detonating key is pressed and detonating is enabled
	bool isDetonating = false;

	int32_t xIdx = -1;

	int32_t yIdx = -1;

    std::vector<std::pair<Obstacle*, sf::Vector2f>> obstaclesHit;
	bool canChangeObstacleAnim = false;

    std::pair<const CollisionComponent*, sf::Vector2f> hitResult = {nullptr, sf::Vector2f()};

	// Method about what will happen when there is an explosion
	void explosionEffect(const sf::Vector2f& direction);

	// Method to determine directions in which the bomb can explode
	bool isDirectionSafe(const sf::Vector2f& position, const sf::Vector2f& direction, float maxDistance);
	
	int32_t getExplosionAnimationID(const sf::Vector2f& direction) const;

	sf::Vector2f alignToGrid(const sf::Vector2f& newPosition);

	sf::Vector2f directionToPosition(sf::Vector2f newDirection);

};
