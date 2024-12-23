#pragma once
#include "InputModule/InputTypes.hpp"
#include "GameModule/Bomb.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include <chrono>

class Animation;

class PlayerCharacter
{
public:
	PlayerCharacter();

	~PlayerCharacter();

	bool init();

	void onMove(void* axis2DState);

	void onBombPlant(void* axis2DState);

	void onBombDetonate(void* buttonState);

	void setCanDetonate(bool detonate) { canDetonate = detonate; }

	void updateAnimation(int32_t id);

	std::shared_ptr<Animation> getCurrentAnimation() const;

	bool getIsUpdated() const { return m_isUpdated; }

	void setIsUpdated(bool isUpdated) { m_isUpdated = isUpdated; }

	sf::Vector2f getCurrentPosition() const;

	void PassThroughBombs(bool pass);

    bool getPassThroughBombs() {return canPassThroughBombs;}

	void updateVelocity(float deltaTime);

	void updateSpeed(float factor);

	void updateBombs(float deltaTime);

	void addMaxBombs();

	void addExplosionRadius();

	void drawBombs(sf::RenderWindow& window);

	CollisionComponent& getCollisionBox() const { return *collisionBox; }
	void startInvincibility();

	void updateInvincibility();

	bool getIsInvincible() const;

	void setIsInvincible(bool isPlayerInvincible) { isInvincible = isPlayerInvincible; }

private:
	int32_t currentAnimation = -1;
	float x = 70.f;
	float y = 70.f;
	float speed = 0.f;
	int32_t maxBombs;
    int32_t bombCapacity;
    float currentExposionRadius;
    float maxExposionRadius;
	float bombDuration;
	float velocity = 0.f;
    bool canPassThroughBombs = false;


	ActionID playerMovement;
	FunctionHandle playerMovementHandle;
	ActionID plantBomb;
	FunctionHandle plantBombHandle;
	ActionID detonateBomb;
	FunctionHandle detonateBombHandle;

	bool canDetonate  = false;		// variable is true if RemoteControlBooster is picked up
	bool isDetonating = false;		// variable is true if DetonateBomb key is pressed

	int32_t bombsToDetonate = 0;	// number of bombs to detonate (if player plants a bomb during detonating, that bomb won't be detonated)

	int32_t leftId;
	int32_t rightId;
	int32_t upId;
	int32_t downId;

	std::unique_ptr<CollisionComponent> collisionBox;

	std::vector<std::shared_ptr<Bomb>> activeBombs;

	bool m_isUpdated = true;

	bool isInvincible = false;
	std::chrono::time_point<std::chrono::high_resolution_clock> invincibilityStartTime;
    float invincibilityDuration;
};