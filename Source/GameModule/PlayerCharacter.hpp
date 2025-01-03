#pragma once
#include "CollisionModule/PlayerCollisionComponent.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "InputModule/InputTypes.hpp"
#include "GameModule/EnemyBase.hpp"
#include "GameModule/Bomb.hpp"
#include <chrono>
#include <set>

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

	void updateAnimation(int32_t id);

	void setIsUpdated(bool isUpdated) { m_isUpdated = isUpdated; }

	void updateVelocity(float deltaTime);

	void updateBombs(float deltaTime);

	void drawBombs(sf::RenderWindow& window);

	void die();

	void resetToStart();
	
	//Getters

	bool getIsUpdated() const { return m_isUpdated; }

    bool getPassThroughBombs() const {return canPassThroughBombs;}
	
	bool getPassThroughFlame() const { return canPassThroughFlames; }
	
	bool getPassThroughWall() const { return canPassThroughWall; }
	
	bool getIsInvincible() const { return isInvincible; }
	
	std::shared_ptr<Animation> getCurrentAnimation() const;

	sf::Vector2f getCurrentPosition() const;

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

	//handlers

	bool handleGateOverlap();

	void handleObstacleOverlap(bool begin);

	void handleBoosterOverlap(Booster* booster);

	//Boosters effect functions

	void addMaxBombs();
	
	void setCanDetonate(bool detonate);
	
	void setPassThroughBombs(bool pass);

	void setPassThroughWall(bool pass);

	void setNewSpeed(float factor);
	
	void setInvincibility(bool isPlayerInvincible);
	
	void setPassThroughFlame(bool pass);
	
	void addExplosionRadius();

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
    bool canPassThroughWall = false;


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