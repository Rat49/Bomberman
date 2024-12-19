#pragma once
#include "InputModule/InputTypes.hpp"
#include "GameModule/Bomb.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/PhysicsModule.hpp"


class Animation;

class PlayerCharacter : public CollisionObject
{
public:
	PlayerCharacter();

	~PlayerCharacter();

	bool init();

	void onMove(void* axis2DState);

	void onBombPlant(void* axis2DState);

	void updateAnimation(int32_t id);

	std::shared_ptr<Animation> getCurrentAnimation() const;

	bool getIsUpdated() const { return m_isUpdated; }

	void setIsUpdated(bool isUpdated) { m_isUpdated = isUpdated; }

	sf::Vector2f getCurrentPosition() const;

	void updateVelocity(float deltaTime);

	void updateSpeed(float factor);

	void updateBombs(float deltaTime);

	void addMaxBombs();

	void drawBombs(sf::RenderWindow& window);

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

    CollisionRectangle& getCollision() { return collision; }

	void onCollision(CollisionComponent* other);

private:
	int32_t currentAnimation = -1;
	float x = 70.f;
	float y = 70.f;
	float speed = 0.f;
	int32_t maxBombs;
    int32_t bombCapacity;
	float bombDuration;
	float velocity = 0.f;

	ActionID playerMovement;
	FunctionHandle playerMovementHandle;
	ActionID plantBomb;
	FunctionHandle plantBombHandle;
	int32_t leftId;
	int32_t rightId;
	int32_t upId;
	int32_t downId;

	std::unique_ptr<CollisionComponent> collisionBox;

    CollisionRectangle collision;

	int32_t collisionBoxID;

	std::vector<std::shared_ptr<Bomb>> activeBombs;

	bool m_isUpdated = true;

	float gridSize = 64.0f;

	bool canMoveLeft  = true;
    bool canMoveRight = true;
    bool canMoveUp    = true;
    bool canMoveDown  = true;

	sf::Vector2f globalStats;
};