#pragma once

#include "Common/Modules.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include "SpriteModule/SpriteModule.hpp"

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

	std::shared_ptr<Animation> getCurrentAnimation() const;

private:
	int32_t currentAnimation = -1;

	int32_t bombIdleID;
	int32_t bombUpID;
	int32_t bombDownID;
	int32_t bombLeftID;
	int32_t bombRightID;
	int32_t bombCenterID;

	// Bomb position
	sf::Vector2f position;
	// Explosion radius
	float explosionRadius;
	// Explosion timer
	float timer;
	// Did the bomb explode
	bool exploded;
	// Graphic representation of a bomb
	sf::CircleShape bombShape;

	// Method about what will happen when there is an explosion
	void explosionEffect(const sf::Vector2f& direction);

	int32_t getExplosionAnimationID(const sf::Vector2f& direction) const;
};
