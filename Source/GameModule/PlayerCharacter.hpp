#pragma once
#include "InputModule/InputTypes.hpp"
#include "GameModule/Bomb.hpp"
#include "CollisionModule/PlayerCollisionComponent.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include <chrono>
#include <set>
#include "GameModule/EnemyBase.hpp"

enum class AllSounds;
class Booster;
class UnbreakableObstacle;
class Obstacle;
class Enemy;
class Animation;

class PlayerCharacter : public CollisionObject
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

	void setPassThroughFlame(bool shouldPassThroughFlame){ canPassThroughFlames = shouldPassThroughFlame; }

	void drawBombs(sf::RenderWindow& window);

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

	void startInvincibility();

	void updateInvincibility();

	bool getIsInvincible() const;

	void setIsInvincible(bool isPlayerInvincible) { isInvincible = isPlayerInvincible; }

	bool handleGateOverlap();

	void handleObstacleOverlap();

	void handleBoosterOverlap(Booster* booster);

	void die();

	void resetToStart();

private:
	int32_t currentAnimation = -1;
	float x = 64.f;
	float y = 64.f;
	float speed = 0.f;
	int32_t maxBombs;
    int32_t bombCapacity;
    float currentExposionRadius;
    float maxExposionRadius;
	float bombDuration;
	float velocity = 0.f;
    bool canPassThroughBombs = false;
    bool canPassThroughFlames = false;


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
    int32_t deathId;

	std::unique_ptr<PlayerCollisionComponent> collisionBox;

	int32_t collisionBoxID;

	float collisionBoxSize = 48.0f;

	std::vector<std::shared_ptr<Bomb>> activeBombs;

	bool m_isUpdated = true;
    bool m_died      = false;

	bool isInvincible = false;
	std::chrono::time_point<std::chrono::high_resolution_clock> invincibilityStartTime;
    float invincibilityDuration;
	float gridSize = 64.0f;

	sf::Vector2f currentDirection = sf::Vector2f(0.0f, 0.0f);
    std::set<std::pair<float, float>> previousDirections;

	sf::Vector2f rightDirection = sf::Vector2f(1.0f, 0.0f);
    sf::Vector2f leftDirection  = sf::Vector2f(-1.0f, 0.0f);
    sf::Vector2f upDirection    = sf::Vector2f(0.0f, 1.0f);
    sf::Vector2f downDirection  = sf::Vector2f(0.0f, -1.0f);

	sf::Vector2f globalStats;
};