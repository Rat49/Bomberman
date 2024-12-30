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
    int32_t bombHorizontalID;
    int32_t bombVerticalID;

	std::unique_ptr<CollisionComponent> collisionBox;

	float gridSize = 64.0f;

	float collisionBoxSize = 50.f;

	// Bomb position
	sf::Vector2f position;

	// Explosion radius
	float explosionRadius = 1.0f;

	// Bomb before explosion timer
	float timer;

	// Detonate cool down
    float detonateCooldown = 500000.0f;

	// Did the bomb explode
	bool exploded = false;
	bool animExploded = false;

	// If true that means detonating key is pressed and detonating is enabled
	bool isDetonating = false;

	bool canChangeObstacleAnim = false;

	// Method about what will happen when there is an explosion
    int32_t explosionEffect(const sf::Vector2f& direction);
	
	int32_t getExplosionAnimationID(const sf::Vector2f& direction) const;

	sf::Vector2f alignToGrid(const sf::Vector2f& newPosition);

	sf::Vector2f directionToPosition(sf::Vector2f newDirection, int32_t numberOfBlocks);

};
